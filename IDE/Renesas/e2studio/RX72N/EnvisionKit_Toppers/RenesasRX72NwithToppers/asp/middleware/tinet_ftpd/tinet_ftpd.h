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
 * tinet_ftpd.h - This file is part of the FTP daemon for tinet
 *
 */

#include <tinet_defs.h>


#define TCP_FTPD_SRV_STACK_SIZE		1024	/* TCP ftpd stack size */
#define TCP_FTPD_SRV_MAIN_PRIORITY	5	/* TCP ECHO server priority */


/*
 *  size of TCP trancever window buffer
 */
//data chanel buffer
#define TCP_FTPD_DATA_SWBUF_SIZE	(TCP_MSS)
#define TCP_FTPD_DATA_RWBUF_SIZE	(TCP_MSS)
//control chanel buffer
#define TCP_FTPD_CONTROL_SWBUF_SIZE	(TCP_MSS)
#define TCP_FTPD_CONTROL_RWBUF_SIZE	(TCP_MSS)

//TCP buffer
//data buffer
extern uint8_t tcp_ftpd_data_swbuf[];
extern uint8_t tcp_ftpd_data_rwbuf[];
//control channel bufferp
extern uint8_t tcp_ftpd_control_swbuf[];
extern uint8_t tcp_ftpd_control_rwbuf[];
