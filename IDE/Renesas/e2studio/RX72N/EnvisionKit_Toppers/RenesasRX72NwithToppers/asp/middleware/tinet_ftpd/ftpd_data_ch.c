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
 * ftpd.c - This file is part of the FTP daemon for lwIP
 *
 */

#include <string.h>

#include <kernel.h>
#include <tinet_defs.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "ftpd_init.h"
#include "ftpd_config.h"
#include "vfs.h"

#include "ftpd_state.h"
#include "ftpd_messeage.h"
#include <t_syslog.h>

//data port define

T_IPV4EP data_dst;

void ftpd_dataclose(ID data_cep_id, struct ftpd_datastate *fsd)
{
	fsd->msgfs->datafs = NULL;
    fsd->buff_len = 0;
    tcp_cls_cep(data_cep_id, 1000);
}

#define TINET_FTPD_SEND_RETRY_NUM 8
static uint32_t send_data(ID data_cep_id, struct ftpd_datastate *fsd)
{
	ER err;
    uint8_t retry_count;

    retry_count = 0;
    do{
      err = tcp_snd_dat(data_cep_id, fsd->data_buff, fsd->buff_len, 1000);
      if (err >= 0)
        return err; //send data success
      retry_count++;
      dly_tsk(100);
    }while(retry_count < TINET_FTPD_SEND_RETRY_NUM);

    fsd->buff_len = 0;
    return 0; //send data fail
}

#define FTPD_DSEND_SIZE 512
static void send_file(struct ftpd_datastate *fsd, ID data_cep_id)
{
  uint32_t len;
  struct ftpd_msgstate *fsm;
  ID msg_cep_id;

  if (!fsd->connected)
    return;
  fsm = fsd->msgfs;
  msg_cep_id = fsm->msg_cep_id;

  if (fsd->vfs_file) {

    while((len = vfs_read(fsd->data_buff, 1, FTPD_DBUFF_SIZE, fsd->vfs_file)) >0){
      fsd->buff_len = len;
      if(send_data(data_cep_id, fsd)==0){
        len=0;
        break;
      }
    }
    if (len == 0) {
      if (vfs_eof(fsd->vfs_file) == 0){
        vfs_close(fsd->vfs_file);
        fsd->vfs_file = NULL;
        ftpd_dataclose(data_cep_id, fsd);
        fsm->datafs = NULL;
        fsm->state = FTPD_IDLE;
        send_msg(msg_cep_id, fsm, msg451);
        return;
      }
    }
  }

  vfs_close(fsd->vfs_file);
  fsd->vfs_file = NULL;
  ftpd_dataclose(data_cep_id, fsd);;
  fsm->datafs = NULL;
  fsm->state = FTPD_IDLE;
  send_msg(msg_cep_id, fsm, msg226);
  return;
}

#if FTPD_ENABLE_FF_DIR

static const char *month_table[12] = {
	"Jan",
	"Feb",
	"Mar",
	"Apr",
	"May",
	"Jun",
	"Jul",
	"Aug",
	"Sep",
	"Oct",
	"Nov",
	"Dez"
};

static void send_next_directory(struct ftpd_datastate *fsd, ID data_cep_id, int shortlist)
{
  uint32_t len, wr_pos;

  while (1) {
	if (fsd->vfs_dirent == NULL)
      fsd->vfs_dirent = vfs_readdir(fsd->vfs_dir);
	if (fsd->vfs_dirent) {
      if (shortlist) {

        len = strlen(fsd->vfs_dirent->name);
        if (ftpd_dbuff_used(fsd) < (len+3)) {
          send_data(data_cep_id, fsd);
        }
        wr_pos = fsd->buff_len;
        strcpy(fsd->data_buff+wr_pos, fsd->vfs_dirent->name);
        strcpy(fsd->data_buff+wr_pos+len, "\r\n");
        fsd->buff_len += len+2;
        fsd->vfs_dirent = NULL;
      }
	} else {
      struct ftpd_msgstate *fsm;
      ID msg_cep_id;

      if (ftpd_dbuff_used(fsd) > 0) {
        send_data(data_cep_id, fsd);
        return;
      }
      fsm = fsd->msgfs;
      msg_cep_id = fsm->msg_cep_id;

      vfs_closedir(fsd->vfs_dir);
      fsd->vfs_dir = NULL;
      ftpd_dataclose(data_cep_id, fsd);
      fsm->datafs = NULL;
      fsm->state = FTPD_IDLE;
      send_msg(msg_cep_id, fsm, msg226);
      return;
	}
  }
}
#endif


static ER rcv_file(struct ftpd_datastate *arg, ID data_cep_id)
{
	struct ftpd_datastate *fsd ;
    ER_UINT rblen;

    struct ftpd_msgstate *fsm;
    ID msg_cep_id;
    fsd = arg;

    while((rblen = tcp_rcv_dat(data_cep_id, fsd->data_buff, FTPD_DBUFF_SIZE, 1000)) > 0){
    	vfs_write(fsd->data_buff, 1, rblen, fsd->vfs_file);
    }
    fsm = fsd->msgfs;
    msg_cep_id = fsm->msg_cep_id;

    vfs_close(fsd->vfs_file);
    fsd->vfs_file = NULL;
    ftpd_dataclose(data_cep_id, fsd);
    fsm->state = FTPD_IDLE;
    send_msg(msg_cep_id, fsm, msg226);

	return E_OK;
}
#define FTPD_TRY_CON_COUNT 5
uint32_t open_dataconnection(ID cep_id, struct ftpd_msgstate *fsm)
{
	ER con_result;
	uint32_t i;
  if (fsm->connection_mode==FTPD_CONNECT_MODE_PASIVE)
    return 0;

  ftpd_init_data_fsm(fsm);

  if (fsm->datafs == NULL) {
    send_msg(cep_id, fsm, msg451);
    return 1;
  }
  memset(fsm->datafs, 0, sizeof(struct ftpd_datastate));
  fsm->datafs->msgfs = fsm;

  for(i = 0;i < FTPD_TRY_CON_COUNT; i++){
    if((con_result = tcp_con_cep(fsm->data_cep_id, &fsm->my_data_ip_port, &fsm->data_ip_port, 1000)) == E_OK)
    	break;
    tslp_tsk(1000);
  }

  if(con_result == E_OK){
    fsm->datafs->connected = 1;
    return 0;
  }
  else
    return -1;
}

void tcp_ftpd_data_srv_task(intptr_t exinf){
  struct ftpd_msgstate *msg_fsm;
  struct ftpd_datastate *data_fsm;
  ER error;
  ID data_cep_id;

  msg_fsm = ftpd_get_fsm((uint32_t) exinf);
  data_fsm = msg_fsm->datafs;

  if(data_fsm == NULL){
    msg_fsm->datafs = NULL;
    return;
  }

  data_cep_id = msg_fsm->data_cep_id;
  if(msg_fsm->connection_mode ==FTPD_CONNECT_MODE_PASIVE){
    if((error = tcp_acp_cep(data_cep_id, TCP_FTPD_DATA_REPID, &data_dst, TMO_FEVR)) != E_OK)
      return;
    data_fsm->connected = 1;
  }
  if (!data_fsm->connected)
    return;
  /*  else {
    if((error = tcp_con_cep(msg_fsm->data_cep_id, &msg_fsm->my_data_ip_port, &msg_fsm->data_ip_port, 1000)) != E_OK){
      return;
    }
    }*/

  switch (msg_fsm->state) {
  case FTPD_RETR: //recive data
    send_file(data_fsm, data_cep_id);
    break;
  case FTPD_STOR:
    rcv_file(data_fsm, data_cep_id);
    break;
#if FTPD_ENABLE_FF_DIR
  case FTPD_LIST:
    send_next_directory(data_fsm, data_cep_id, 0);
    break;
  case FTPD_NLST:
    send_next_directory(data_fsm, data_cep_id, 1);
    break;
#endif
  default:
    break;
  }
  ext_tsk();
}
