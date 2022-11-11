/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2010-2019 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/


#ifndef DHCP_C_H
#define DHCP_C_H

/******************************************************************************
Macro definitions
******************************************************************************/
/* Please define the same price as  _t4_channel_num variable in config_tcpudp.c. */
/* 0 = BLOCKING, 1 = NON_BLOCKING */
#define APPLICATION_T4_BLOCKING_TYPE (0)

#define DEBUG_PRINT

/******************************************************************************
Macro definitions
******************************************************************************/
#define CEPID_BEGIN           (1)
#define CEPID_END             (1)
#define CEP_NUM               (1)

#define T4_CLOSED        (0)
#define T4_ACCEPT        (1)
#define T4_ESTABLISHED   (2)
#define T4_CLOSE_WAIT    (3)
#define T4_LAST_ACK      (4)
#define T4_FIN_WAIT1     (5)
#define T4_TIME_WAIT     (6)
#define T4_CANCELING     (7)
#define T4_SENDING       (8)
#define T4_RESET_WAIT    (255)
#define DEBUG_PRINT
/******************************************************************************
Typedef definitions
******************************************************************************/
typedef struct _CEP
{
    uint32_t    status;
    T_IPV4EP    dst_addr;
    T_IPV4EP    src_addr;
    int32_t     current_rcv_data_len;
    int32_t     total_rcv_len;
    UB          rcv_buf[1460];
    UB          snd_buf[1460];
    int32_t     _1sec_counter;
    int32_t     _1sec_timer;
    int32_t     pre_1sec_timer;
} st_cep_t;
/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
extern const UB _t4_channel_num;
extern const UB _t4_dhcp_enable;
extern T_TCP_CREP tcp_crep[];
extern T_TCP_CCEP tcp_ccep[];
extern T_UDP_CCEP udp_ccep[];
extern const H __tcprepn;
extern const H __tcpcepn;
extern const H __udpcepn;

void dhcp_client(void);
ER tcp_nonblocking_callback(ID cepid, FN fncd , VP p_parblk);
ER system_callback(UB channel, UW eventid, VP param);
void receive_cancel_timer(void);

#endif /* #ifndef DHCP_C_H */
