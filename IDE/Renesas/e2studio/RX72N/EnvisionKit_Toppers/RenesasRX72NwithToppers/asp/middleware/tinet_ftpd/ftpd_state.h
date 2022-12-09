/*
 * Copyright 2016 Hisashi Hata.
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
 * ftpd_state.h - This file is part of the FTP daemon for tinet
 *
 */
#ifndef FTPD_STATE_H
#define FTPD_STATE_H

#include "vfs.h"
#include "kernel.h"
#include <netinet/tcp.h>
#include <netinet/in.h>

enum ftpd_state_e {
	FTPD_USER,
	FTPD_PASS,
	FTPD_IDLE,
	FTPD_NLST,
	FTPD_LIST,
	FTPD_RETR,
	FTPD_RNFR,
	FTPD_STOR,
	FTPD_QUIT
};
//connection mode
#define FTPD_CONNECT_MODE_PASIVE 1
#define FTPD_CONNECT_MODE_ACTIVE 0

#define FTPD_DBUFF_SIZE 512
#define ftpd_dbuff_used(fsm) (FTPD_DBUFF_SIZE - fsm->buff_len)

struct ftpd_datastate {
  uint32_t connected;
  vfs_dir_t *vfs_dir;
  vfs_dirent_t *vfs_dirent;
  vfs_file_t *vfs_file;
  uint8_t data_buff[FTPD_DBUFF_SIZE];
  uint32_t buff_len;
  struct ftpd_msgstate *msgfs;
};

struct ftpd_msgstate {
  uint32_t ch_id;
  enum ftpd_state_e state;
  uint32_t connection_mode;
  vfs_t *vfs;
  ID data_tsk_id;
  T_IPV4EP my_data_ip_port;
  T_IPV4EP data_ip_port;
  ID data_cep_id;
  ID msg_cep_id;
  struct ftpd_datastate *datafs;
  //  int passive;
  char *renamefrom;
};

#endif
