/*
 * Copyright 2016 Hisashi Hata
 * Copyright (c) 2002 Florian Schulze.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the authors nor the names of the contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * ftpd.c - This file is part of the FTP daemon for tinet
 *
 */

#include "ftpd_config.h"

#include <ctype.h>
#include <string.h>
#include <kernel.h>
#include <tinet_defs.h>

#include <t_syslog.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "vfs.h"
#include "ftpd_state.h"
#include "ftpd_messeage.h"
#include "ftpd_data_ch.h"
#include "ftpd_arg_dec.h"
#include "ftpd_init.h"

static T_IPV4EP		ftpd_control_dst;

static void ftpd_msgclose(ID cep_id, struct ftpd_msgstate *fsm);

static void cmd_user(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	send_msg(cep_id, fsm, msg331);
	fsm->state = FTPD_PASS;
	/*
	   send_msg(pcb, fs, msgLoginFailed);
	   fs->state = FTPD_QUIT;
	 */
}

static void cmd_pass(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	send_msg(cep_id, fsm, msg230);
	fsm->state = FTPD_IDLE;
	/*
	   send_msg(pcb, fs, msgLoginFailed);
	   fs->state = FTPD_QUIT;
	 */
}

static void cmd_port(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
  int32_t nr;
  uint32_t dec_val[6];

  nr = ftpd_num_arg_dec(arg, dec_val, 6);

  if (nr < 0) {
    send_msg(cep_id, fsm, msg501);
  } else {
    fsm->data_ip_port.ipaddr = ((((uint32_t)dec_val[0])<<24)|(((uint32_t)dec_val[1]) <<16)|(((uint32_t)dec_val[2])<<8)| (uint32_t)dec_val[3]);
    fsm->data_ip_port.portno = ((uint16_t) dec_val[4] << 8) | (uint16_t) dec_val[5];
    send_msg(cep_id, fsm, msg200);
  }
}

static void cmd_quit(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	send_msg(cep_id, fsm, msg221);
	fsm->state = FTPD_QUIT;

}

#if FTPD_ENABLE_FF_DIR

static void cmd_cwd(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	if (!vfs_chdir(fsm->vfs, arg)) {
		send_msg(cep_id, fsm, msg250);
	} else {
		send_msg(cep_id, fsm, msg550);
	}
}

static void cmd_cdup(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	if (!vfs_chdir(fsm->vfs, "..")) {
		send_msg(cep_id, fsm, msg250);
	} else {
		send_msg(cep_id, fsm, msg550);
	}
}

static void cmd_pwd(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	uint8_t path[32];
    //temp
    //	if ((path = vfs_getcwd(fsm->vfs, &path, 0))) {
      //      send_msg(cep_id, fsm, msg257PWD, path);
   send_msg(cep_id, fsm, msg257PWD);        //temp
      //	}
}

static void cmd_list_common(const uint8_t *arg, ID cep_id, struct ftpd_msgstate *fsm, int shortlist)
{
  uint8_t path[32];
  vfs_dir_t *vfs_dir;
  int8_t *cwd;

  cwd = vfs_getcwd(fsm->vfs, path, 32);
  if ((!cwd)) {
    send_msg(cep_id, fsm, msg451);
    return;
  }
  vfs_dir = vfs_opendir(ftpd_get_vfs_dir(fsm->ch_id), cwd);
  if (!vfs_dir) {
    send_msg(cep_id, fsm, msg451);
    return;
  }

  if (open_dataconnection(cep_id, fsm) != 0) {
    send_msg(cep_id, fsm, msg550);
    vfs_closedir(vfs_dir);
    return;
  }

  fsm->datafs->vfs_dir = vfs_dir;
  fsm->datafs->vfs_dirent = NULL;
  if (shortlist != 0)
    fsm->state = FTPD_NLST;
  else
	fsm->state = FTPD_LIST;

  send_msg(cep_id, fsm, msg150);
}

static void cmd_nlst(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
  cmd_list_common(arg, cep_id, fsm, 1);
}

static void cmd_list(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	cmd_list_common(arg, cep_id, fsm, 0);
}
#endif

static void cmd_retr(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	vfs_file_t *vfs_file;
	vfs_stat_t st;

	if(vfs_stat((vfs_t*)fsm->vfs, arg, &st) != 0){
      send_msg(cep_id, fsm, msg550);
      return;
    }

	if (!VFS_ISREG(st.st_mode)) {
      send_msg(cep_id, fsm, msg550);
      return;
	}
	vfs_file = vfs_open((vfs_t*)ftpd_get_vfs_file(fsm->ch_id), arg, (const int8_t*)"rb");
	if (!vfs_file) {
      send_msg(cep_id, fsm, msg550);
      return;
	}

    //	send_msg(cep_id, fsm, msg150recv, arg, st.st_size);
	if ((open_dataconnection(cep_id, fsm)) != 0) {
      vfs_close(vfs_file);
      send_msg(cep_id, fsm, msg550);
      return;
	}
    send_msg(cep_id, fsm, msg150recv); //temp

	fsm->datafs->vfs_file = vfs_file;
	fsm->state = FTPD_RETR;
	act_tsk(fsm->data_tsk_id);
}

static void cmd_stor(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	vfs_file_t *vfs_file;

	vfs_file = vfs_open((vfs_t*)ftpd_get_vfs_file(fsm->ch_id), arg, (const int8_t*)"wb");
	if (!vfs_file) {
      send_msg(cep_id, fsm, msg550);
      return;
	}

    //	send_msg(cep_id, fsm, msg150stor, arg); temp
    send_msg(cep_id, fsm, msg150stor);
	if (open_dataconnection(cep_id, fsm) != 0) {
      send_msg(cep_id, fsm, msg550);
      vfs_close(vfs_file);
      return;
	}

	fsm->datafs->vfs_file = vfs_file;
	fsm->state = FTPD_STOR;
	act_tsk(fsm->data_tsk_id);
}

static void cmd_noop(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	send_msg(cep_id, fsm, msg200);
}

static void cmd_syst(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
  //	send_msg(cep_id, fsm, msg214SYST, "UNIX"); temp
  send_msg(cep_id, fsm, msg214SYST);
}

static void cmd_pasv(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
  ftpd_init_data_fsm(fsm);

  fsm->datafs->msgfs = fsm;

  fsm->connection_mode = FTPD_CONNECT_MODE_PASIVE;
  fsm->datafs->connected = 0;
  //temp
  //send_msg(pcb, fsm, msg227, ip4_addr1(ip_2_ip4(&pcb->local_ip)), ip4_addr2(ip_2_ip4(&pcb->local_ip)), ip4_addr3(ip_2_ip4(&pcb->local_ip)), ip4_addr4(ip_2_ip4(&pcb->local_ip)), (fsm->dataport >> 8) & 0xff, (fsm->dataport) & 0xff);
  send_msg(cep_id, fsm, msg227_short);
}


/*tinet not support
static void cmd_abrt(const uint8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	if (fsm->datafs != NULL) {
      //tcp_abort(cep_id); temp
		sfifo_close(&fsm->datafs->fifo);
		fsm->datafs = NULL;
	}
	fsm->state = FTPD_IDLE;
}
*/
static void cmd_type(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
  //	dbg_printf("Got TYPE -%s-\n", arg);
	send_msg(cep_id, fsm, msg200);
}

static void cmd_mode(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
  //	dbg_printf("Got MODE -%s-\n", arg);
	send_msg(cep_id, fsm, msg502);
}

uint8_t ftpd_renamefrom[32];

static void cmd_rnfr(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	if (arg == NULL) {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (*arg == '\0') {
		send_msg(cep_id, fsm, msg501);
		return;
	}

	fsm->renamefrom = ftpd_renamefrom;
	if (fsm->renamefrom == NULL) {
		send_msg(cep_id, fsm, msg451);
		return;
	}
	strcpy(fsm->renamefrom, arg);
	fsm->state = FTPD_RNFR;
	send_msg(cep_id, fsm, msg350);
}

static void cmd_rnto(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	if (fsm->state != FTPD_RNFR) {
		send_msg(cep_id, fsm, msg503);
		return;
	}
	fsm->state = FTPD_IDLE;
	if (arg == NULL) {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (*arg == '\0') {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (vfs_rename(fsm->vfs, fsm->renamefrom, arg)) {
		send_msg(cep_id, fsm, msg450);
	} else {
		send_msg(cep_id, fsm, msg250);
	}
}

#if FTPD_ENABLE_FF_DIR
static void cmd_mkd(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	if (arg == NULL) {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (*arg == '\0') {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (vfs_mkdir(fsm->vfs, arg, VFS_IRWXU | VFS_IRWXG | VFS_IRWXO) != 0) {
		send_msg(cep_id, fsm, msg550);
	} else {
		send_msg(cep_id, fsm, msg257);
	}
}

static void cmd_rmd(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	vfs_stat_t st;

	if (arg == NULL) {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (*arg == '\0') {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (vfs_stat(fsm->vfs, arg, &st) != 0) {
		send_msg(cep_id, fsm, msg550);
		return;
	}
	if (!VFS_ISDIR(st.st_mode)) {
		send_msg(cep_id, fsm, msg550);
		return;
	}
	if (vfs_rmdir(fsm->vfs, arg) != 0) {
		send_msg(cep_id, fsm, msg550);
	} else {
		send_msg(cep_id, fsm, msg250);
	}
}
#endif

static void cmd_dele(const int8_t *arg, ID cep_id, struct ftpd_msgstate *fsm)
{
	vfs_stat_t st;

	if (arg == NULL) {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (*arg == '\0') {
		send_msg(cep_id, fsm, msg501);
		return;
	}
	if (vfs_stat(fsm->vfs, arg, &st) != 0) {
		send_msg(cep_id, fsm, msg550);
		return;
	}
	if (!VFS_ISREG(st.st_mode)) {
		send_msg(cep_id, fsm, msg550);
		return;
	}
	if (vfs_remove(fsm->vfs, arg) != 0) {
		send_msg(cep_id, fsm, msg550);
	} else {
		send_msg(cep_id, fsm, msg250);
	}
}

struct ftpd_command {
	int8_t *cmd;
	void (*func) (const int8_t *arg, ID cep_id, struct ftpd_msgstate * fsm);
};

static struct ftpd_command ftpd_commands[] = {
  {(int8_t*)"USER", cmd_user},
  {(int8_t*)"PASS", cmd_pass},
  {(int8_t*)"PORT", cmd_port},
  {(int8_t*)"QUIT", cmd_quit},
  {(int8_t*)"RETR", cmd_retr},
  {(int8_t*)"STOR", cmd_stor},
  {(int8_t*)"NOOP", cmd_noop},
  {(int8_t*)"SYST", cmd_syst},
  //	{"ABOR", cmd_abrt},
  {(int8_t*)"TYPE", cmd_type},
  {(int8_t*)"MODE", cmd_mode},
  {(int8_t*)"RNFR", cmd_rnfr},
  {(int8_t*)"RNTO", cmd_rnto},
  {(int8_t*)"DELE", cmd_dele},
  {(int8_t*)"PASV", cmd_pasv},
#if FTPD_ENABLE_FF_DIR
  {(int8_t*)"CWD", cmd_cwd},
  {(int8_t*)"CDUP", cmd_cdup},
  {(int8_t*)"PWD", cmd_pwd},
  {(int8_t*)"XPWD", cmd_pwd},
  {(int8_t*)"NLST", cmd_nlst},
  {(int8_t*)"LIST", cmd_list},
  {(int8_t*)"MKD", cmd_mkd},
  {(int8_t*)"XMKD", cmd_mkd},
  {(int8_t*)"RMD", cmd_rmd},
  {(int8_t*)"XRMD", cmd_rmd},
#endif
  {NULL, NULL}
};

void send_msg(ID cep_id, struct ftpd_msgstate *fsm, const int8_t *msg)
{
	uint8_t buffer[128];
	int len;

    tcp_snd_dat(cep_id, msg, strlen(msg), 1000);

}

static void ftpd_msgerr(void *arg, ER err)
{
	struct ftpd_msgstate *fsm = arg;

    //dbg_printf("ftpd_msgerr: %s (%i)\n", lwip_strerr(err), err);
	if (fsm == NULL)
		return;
	if (fsm->datafs)
		ftpd_dataclose(fsm->data_cep_id, fsm->datafs);
	vfs_close(fsm->vfs);
	fsm->vfs = NULL;
	fsm->renamefrom = NULL;
}

static void ftpd_msgclose(ID cep_id, struct ftpd_msgstate *fsm)
{
	if (fsm->datafs)
		ftpd_dataclose(fsm->data_cep_id, fsm->datafs);
	vfs_close(fsm->vfs);
	fsm->vfs = NULL;
	fsm->renamefrom = NULL;
	fsm->state = FTPD_IDLE;
}

#define FTPD_CONTROL_RBUF_SIZE 32

static ER ftpd_msgrecv(struct ftpd_msgstate *fsm, ID cep_id, uint8_t *p_buf, uint32_t rlen)
{
	int8_t text[FTPD_CONTROL_RBUF_SIZE+1];
    uint32_t buf_len;

    buf_len = (rlen > FTPD_CONTROL_RBUF_SIZE) ? FTPD_CONTROL_RBUF_SIZE : rlen;

    /* Inform TCP that we have taken the data. */
    int8_t cmd[5];
    int8_t *pt;
    struct ftpd_command *ftpd_cmd;

    memmove(text, p_buf, buf_len);
    text[buf_len] = '\0';

    pt = &text[strlen(text) - 1];
    while (((*pt == '\r') || (*pt == '\n')) && pt >= text)
      *pt-- = '\0';

    //dbg_printf("query: %s\n", text);

    strncpy(cmd, text, 4);
    for (pt = cmd; isalpha(*pt) && pt < &cmd[4]; pt++)
      *pt = toupper(*pt);
    *pt = '\0';

    for (ftpd_cmd = ftpd_commands; ftpd_cmd->cmd != NULL; ftpd_cmd++) {
      if (!strcmp(ftpd_cmd->cmd, cmd))
        break;
    }

    if (strlen(text) < (strlen(cmd) + 1))
      pt = "";
    else
      pt = &text[strlen(cmd) + 1];

    if (ftpd_cmd->func)
      ftpd_cmd->func((int8_t*)pt, cep_id, fsm);
    else
      send_msg(cep_id, fsm, msg502);

	return E_OK;
}

static ER ftpd_msgaccept(struct ftpd_msgstate* fsm)
{

	/* Initialize the structure. */
	fsm->state = FTPD_IDLE;
	fsm->vfs = vfs_openfs();
	if (!fsm->vfs) {
		return E_PAR;
	}
	return E_OK;
}

FATFS fatfs;

void tcp_ftpd_control_srv_task(intptr_t exinf){
  ID tskid;
  ER error = E_OK;
  ER_UINT rblen;
  uint8_t rbuf[64];
  struct ftpd_msgstate *fsm;

  while(true){
    fsm = ftpd_init_conf((uint32_t)exinf);

    if((error = tcp_acp_cep(fsm->msg_cep_id, TCP_FTPD_CONTROL_REPID, &ftpd_control_dst, TMO_FEVR)) != E_OK){
      continue;
    }
    else{
      ftpd_msgaccept(fsm);
    }

    //send initial message
	send_msg(fsm->msg_cep_id, fsm, msg220);
    while(true) {
      if ((rblen = tcp_rcv_dat((ID)fsm->msg_cep_id, rbuf, 64, TMO_FEVR)) < 0) {
		break;
      }
      if(rblen == 0){ //rcv FIN
        ftpd_msgclose((ID)fsm->msg_cep_id, fsm);
        break;
      }
      else{
        ftpd_msgrecv(fsm, fsm->msg_cep_id, rbuf, rblen);
        if(fsm->state == FTPD_QUIT){
        	ftpd_msgclose((ID)fsm->msg_cep_id, fsm);
        	tcp_cls_cep((ID)fsm->msg_cep_id, 1000);
        	break;
        }

      }
    }
  }

}
