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
 * ftpd_config.c - This file is part of the FTP daemon for tinet
 *
 */

#ifndef FTPD_CONFIG_H
#define FTPD_CONFIG_H

#include <tinet_defs.h>
#include "vfs.h"

#define TCP_FTPD_CONTROL_PRIORITY 5
#define	TCP_FTPD_CONTROL_STACK_SIZE 512

#define TCP_FTPD_DATA_PRIORITY 5
#define	TCP_FTPD_DATA_STACK_SIZE 512

#define FTPD_CONTROL_PORT_0 21
#define FTPD_DATA_PORT_0 20

#define FTPD_CH_ID 0


extern void tcp_ftpd_control_srv_task(intptr_t exinf);
extern void tcp_ftpd_data_srv_task(intptr_t exinf);


//file system config
#if _FS_RPATH >= 2
#define FTPD_ENABLE_FF_DIR
#endif

#endif
