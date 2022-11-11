/*
 * Copyright (c) 2016-  Hisashi Hata
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the tinet_shell
 *
 * Author: Hisashi Hata
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

#include <string.h>

#include <kernel.h>
#include "tinet_cfg.h"

#include <netinet/in.h>
#include <netinet/in_itron.h>
#include <netinet/tcp.h>

#include "middleware/tinet_shell/shell.h"
#include "middleware/tinet_shell/tinet_shell.h"
#define WIN32
#ifdef WIN32
#define NEWLINE "\r\n"
#else /* WIN32 */
#define NEWLINE "\n"
#endif /* WIN32 */

/** Define this to 1 if you want to echo back all received characters
 * (e.g. so they are displayed on a remote telnet)
 */
#ifndef SHELL_ECHO
#define SHELL_ECHO 0
#endif

struct shell_io_param {
  ID rep_id;
  ID cep_id;
  uint32_t port_num;
};

static struct shell_io_param shell_io = {TCP_SHELL_REPID, TCP_SHELL_CEPID, };

#define NOT_CONNECT 0
#define CONNECTED 1

static uint8_t con_status = NOT_CONNECT;

void shell_close_connection(){
	if(con_status == CONNECTED)
		tcp_cls_cep(TCP_SHELL_CEPID, 1000);
	con_status = NOT_CONNECT;
	return;
}

struct command {
  int8_t (* exec)(uint8_t, int8_t**);
  int8_t nargs;
  int8_t *args[10];
};

static void
sendstr(const char *str)
{
  tcp_snd_dat(shell_io.cep_id, (void *)str, strlen(str), 1000);
}

void shell_print(const char *str)
{
  sendstr(str);
}

/* followin strings are help string. plese modify if you need.*/
int8_t cmd_help(uint8_t argc, int8_t *argv[]);

static int8_t close_msg[] = "close connection."NEWLINE;
int8_t cmd_close(uint8_t argc, int8_t *argv[])
{
  sendstr(close_msg);
  return ECLOSE;
}

int8_t cmd_dummy(uint8_t argc, int8_t *argv[]){
  return ESUCCESS;
}

shell_cmd_t tinet_reserv_cmd[] = {
  {"help", 0, cmd_help, "help: display the help message."NEWLINE},
  {"exit", 0, cmd_close, "exit: exit shell and close connection."NEWLINE},
  {"quit", 0, cmd_close, NULL},
  {"^]", 0, cmd_close, NULL},
  {NULL, 0, NULL, NULL}
};

shell_cmd_t dummy_cmd = {NULL, 0, cmd_dummy, NULL};

/*register user shell command */
shell_cmd_t* tinet_usr_cmd = NULL;

void put_help_msg(shell_cmd_t *cur_cmd){
  while(cur_cmd->cmd_str != NULL){
    if(cur_cmd->help_msg != NULL){
      sendstr(cur_cmd->help_msg);
    }
    cur_cmd++;
  }
  return;
}


int8_t cmd_help(uint8_t argc, int8_t *argv[])
{
  put_help_msg(tinet_reserv_cmd);
  if(tinet_usr_cmd != NULL)
    put_help_msg(tinet_usr_cmd);
  return ESUCCESS;
}

void shell_set_usr_cmd(shell_cmd_t* usr_cmd_table){
  tinet_usr_cmd = usr_cmd_table;
}

static shell_cmd_t * search_calling_cmd(shell_cmd_t* cmd_table, int8_t* cmd_str){
  shell_cmd_t *shell_cmd;
  uint16_t cmd_len;
  int8_t check_char;

  cmd_len = 0;
  check_char = *cmd_str;
  while((check_char != '\n') && (check_char != '\r') && (check_char != ' ')){
    cmd_len++;
    check_char = cmd_str[cmd_len];
  }

  if(cmd_len == 0)
	  return &dummy_cmd;

  shell_cmd = cmd_table;
  while(shell_cmd->cmd_str != NULL){
    if(cmd_len == strlen((char*)shell_cmd->cmd_str)){
      if (strncmp((const int8_t *)cmd_str, shell_cmd->cmd_str, strlen(shell_cmd->cmd_str)) == 0) {
        break;
      }
    }
    shell_cmd ++;
  }

  if(shell_cmd->cmd_str == NULL){
    return NULL;
  }
  return shell_cmd;
}

static int8_t
parse_command(struct command *com, uint32_t len, int8_t *sbuff)
{
  uint8_t * com_str;
  uint16_t i, bufp;
  shell_cmd_t *shell_cmd;

  //space skip
  com_str = sbuff;
  while(*com_str == ' ')
	  com_str++;

  //check reserved command
  shell_cmd = search_calling_cmd(tinet_reserv_cmd , com_str);

  //check user defined command
  if((shell_cmd == NULL) && (tinet_usr_cmd != NULL)){
    shell_cmd = search_calling_cmd(tinet_usr_cmd , com_str);
  }

  if(shell_cmd == NULL){
    return ESYNTAX;
  }

  com->exec = shell_cmd->call_stub;
  com->nargs = shell_cmd->narg;

  if (com->nargs == 0) {
    return ESUCCESS;
  }

  bufp = strlen(shell_cmd->cmd_str);
  for(i = 0; i < 10; i++) {
    for(; bufp < len && com_str[bufp] == ' '; bufp++);
    if (com_str[bufp] == '\r' || com_str[bufp] == '\n') {
      com_str[bufp] = '\0';
      if (i < com->nargs - 1) {
        com->nargs = i;
        return ESUCCESS_FEWARGC;
      }
      if (i > com->nargs - 1) {
        return ETOOMANY;
      }
      break;
    }
    if (bufp > len) {
      return ETOOFEW;
    }
    com->args[i] = (int8_t *)&com_str[bufp];
    for(; bufp < len && com_str[bufp] != ' ' && com_str[bufp] != '\r' && com_str[bufp] != '\n'; bufp++) {
      if (com_str[bufp] == '\\') {
        com_str[bufp] = ' ';
      }
    }
    if (bufp > len) {
      return ESYNTAX;
    }
    com_str[bufp] = '\0';
    bufp++;
    if (i == com->nargs - 1) {
      break;
    }
  }

  return ESUCCESS;
}


/*-----------------------------------------------------------------------------------*/
static void
shell_error(ER err)
{
  switch (err) {
  case ESYNTAX:
    sendstr("## Syntax error"NEWLINE);
    break;
  case ETOOFEW:
    sendstr("## Too few arguments to command given"NEWLINE);
    break;
  case ETOOMANY:
    sendstr("## Too many arguments to command given"NEWLINE);
    break;
  default:
    /* unknown error, don't assert here */
    break;
  }
}
/*-----------------------------------------------------------------------------------*/
static void
prompt()
{
  sendstr("> ");
}
/*-----------------------------------------------------------------------------------*/
#define SHELL_BUFFER_SIZE 128
uint8_t shell_net_buf[SHELL_BUFFER_SIZE];
int8_t shell_buf[SHELL_BUFFER_SIZE];

static T_IPV4EP	shell_dst;


static void
shell_main()
{
  ER_UINT cur_len;
  ER_UINT com_len;
  struct command com;
  ER err;

  com_len = 0;
  prompt();
  do {
    if((cur_len = tcp_rcv_dat(TCP_SHELL_CEPID, shell_net_buf, TCP_SHELL_RWBUF_SIZE, TMO_FEVR)) <= 0){
      shell_close_connection();
      break;
    }

    if(cur_len+com_len > SHELL_BUFFER_SIZE)
      cur_len = SHELL_BUFFER_SIZE - cur_len -1;

    memcpy(&shell_buf[com_len], shell_net_buf, cur_len);
#if SHELL_ECHO
    if (echomem != NULL) {
      tcp_snd_dat(TCP_SHELL_CEPID, &shell_buf[com_len], cur_len, 1000);
    }
#endif /* SHELL_ECHO */

    com_len += cur_len;
    //telnet command code check
    if (((shell_buf[0] &0xf0) == 0xf0) ||  ((shell_buf[1] & 0xf0) == 0xf0)) {
      com_len = 0;
    }
    else if (((com_len > 0) && ((shell_buf[com_len-1] == '\r') || (shell_buf[com_len-1] == '\n'))) ||
      (com_len >= SHELL_BUFFER_SIZE)) {
      err = parse_command(&com, com_len, shell_buf);
      if (err >= ESUCCESS) {
        err = com.exec(com.nargs, com.args);
        if (err == ECLOSE){
          shell_close_connection();
          break;
        }
        else if (err != ESUCCESS) {
          shell_error(err);
        }
      }
      else {
        sendstr("Error command not exist."NEWLINE);
      }
      prompt();
      com_len = 0;
    }
  } while (1);
}
/*-----------------------------------------------------------------------------------*/
void
shell_task(intptr_t exinf)
{
  while (1) {
    if(tcp_acp_cep(shell_io.cep_id, TCP_SHELL_REPID, &shell_dst, TMO_FEVR) == E_OK){
      con_status = CONNECTED;
      shell_main();
    }
  }
}
/*-----------------------------------------------------------------------------------*/
