/*
 * Copyright 2016 Hisashi Hata
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
 * ftpd_init.c - This file is part of the FTP daemon for tinet
 *
 */
#include <string.h>
#include <kernel.h>
#include <kernel_cfg.h>
#include "ftpd_config.h"
#include "ftpd_init.h"
#include <tinet_app_config.h>
#include "tinet_cfg.h"
#include "tinet_ftpd.h"
#include "vfs.h"


#define FTPD_NUM_CONNECTION 1
struct ftpd_msgstate ftpd_control_fsm[FTPD_NUM_CONNECTION];
//control fsm
struct ftpd_datastate ftpd_data_fsm[FTPD_NUM_CONNECTION];
//for vfs
vfs_file_t ftpd_vfs_file[FTPD_NUM_CONNECTION];
vfs_dir_t ftpd_vfs_dir[FTPD_NUM_CONNECTION];
                              
uint8_t tcp_ftpd_control_swbuf[TCP_FTPD_CONTROL_SWBUF_SIZE];
uint8_t tcp_ftpd_control_rwbuf[TCP_FTPD_CONTROL_RWBUF_SIZE];
uint8_t tcp_ftpd_data_swbuf[TCP_FTPD_DATA_SWBUF_SIZE];
uint8_t tcp_ftpd_data_rwbuf[TCP_FTPD_DATA_RWBUF_SIZE];



struct ftpd_msgstate * ftpd_init_conf(uint32_t num_con){
  struct ftpd_msgstate *fsm;
  
  fsm = &ftpd_control_fsm[num_con];
  if(num_con == 0){
    fsm->ch_id = num_con;
    fsm->state = FTPD_IDLE;
    fsm->vfs = NULL;
    fsm->data_tsk_id = TCP_FTPD_DATA_TASK;
    fsm->my_data_ip_port.ipaddr = IPV4_ADDR_LOCAL;
    fsm->my_data_ip_port.portno = FTPD_DATA_PORT_0;
    fsm->data_ip_port.ipaddr = 0;
    fsm->data_ip_port.portno = 0;
    fsm->datafs = NULL;
    fsm->renamefrom = NULL;
    fsm->data_cep_id = TCP_FTPD_DATA_CEPID;
    fsm->msg_cep_id = TCP_FTPD_CONTROL_CEPID;
  }
  return fsm;
}

void ftpd_init_data_fsm(struct ftpd_msgstate* msg_fsm){
  msg_fsm->datafs = &ftpd_data_fsm[msg_fsm->ch_id];
  memset(msg_fsm->datafs, 0, sizeof(struct ftpd_datastate));
}

struct ftpd_msgstate * ftpd_get_fsm(uint32_t num_con){
  return &ftpd_control_fsm[num_con];
}
  
vfs_file_t* ftpd_get_vfs_file(uint32_t num_con){
  return &ftpd_vfs_file[num_con];
}

vfs_dir_t* ftpd_get_vfs_dir(uint32_t num_con){
  return &ftpd_vfs_dir[num_con];
}
