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
* Copyright (C) 2011-2021 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

/*******************************************************************************
* File Name     : t4_driver.c
* Version       : 1.09
* Tool-Chain    : C/C++ Compiler Package for RX Family
* Description   : T4 ethernet driver interface program.
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 15.01.2011 ---   First Release.
*               : 31.08.2011 ----   Cleanup source code.
*               : 06.11.2012 ----   Added RX63N support.
*               : 19.02.2014 ----   Support M3S-T4-Tiny V.2.00.
*               : 05.01.2015 ----   Fixed include file.
*               : 01.12.2015 ----   get_random_number add.
*               : 15.04.2016 ----   Fixed count timing for 10ms tick software
*               :                     counter variable "tcpudp_time_cnt".
*               : 09.05.2016 ----   Added RX63N and RX65N support.
*                                   Supported the LinkProcess function execution during processing of the interrupt.
*               : 10.12.2018 ----   Fixed Random number conflict.
*               :                   Fixed IP address conflict.
*               : 20.06.2019 ----   Added support GCC RX compiler and IAR RX compiler .
*               : 29.01.2021 ----   Updated operation of random number generator.
*                                   Added hash value generation function.
******************************************************************************/

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include <stdbool.h>
#include <string.h>
#include "platform.h"
#include "r_t4_driver_rx_config.h"
#include "r_t4_itcpip.h"
#include "r_ether_rx_if.h"
#include "timer.h"

#if R_BSP_VERSION_MAJOR < 5
#error "This module must use BSP module of Rev.5.00 or higher. Please use the BSP module of Rev.5.00 or higher."
#endif
#if (defined BSP_MCU_RX231 || defined BSP_MCU_RX23W) && (BSP_CFG_MCU_PART_VERSION == 0xB)  /* B */
#include "r_tsip_rx_if.h"
#elif (defined BSP_MCU_RX66T || defined BSP_MCU_RX72T) && ((BSP_CFG_MCU_PART_FUNCTION == 0xE /* E */) || \
    (BSP_CFG_MCU_PART_FUNCTION == 0xF /* F */) || (BSP_CFG_MCU_PART_FUNCTION == 0x10 /* G */))
#include "r_tsip_rx_if.h"
#elif (defined BSP_MCU_RX65N || defined BSP_MCU_RX651) && (BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true)
#include "r_tsip_rx_if.h"
#elif (defined BSP_MCU_RX72M || defined BSP_MCU_RX72N || defined BSP_MCU_RX66N) && \
    (BSP_CFG_MCU_PART_FUNCTION == 0x11 /* H */)
//#include "r_tsip_rx_if.h"
#else
#warning "Your MCU does not support TSIP functions. It is better to use RX Family that support TSIP functions for more security. Vulnerability reference: https://www.ipa.go.jp/security/rfc/RFC1948EN.html"
#endif  /* defined BSP_MCU_RX231 || defined BSP_MCU_RX23W && BSP_CFG_MCU_PART_VERSION == 0xB */

#if   BSP_CFG_RTOS_USED == 0    // Non-OS
#elif BSP_CFG_RTOS_USED == 1    // FreeRTOS
#include "FreeRTOS_usr_cfg.h"
#elif BSP_CFG_RTOS_USED == 2    // SEGGER embOS
#elif BSP_CFG_RTOS_USED == 3    // Micrium MicroC/OS
#elif BSP_CFG_RTOS_USED == 4    // Renesas RI600V4 & RI600PX
#include "kernel.h"
#include "kernel_cfg.h"

#elif BSP_CFG_RTOS_USED == 6

//#include "kernel_id.h"
#else
#error "no valid rtos definition"
#endif

/******************************************************************************
Macro definitions
******************************************************************************/

#define ETHER_BUFSIZE_MIN 60
#define BSP_CFG_RTOS_USED 4 //wata
#if   (BSP_CFG_RTOS_USED >= 1)
#define MAX_TCPCEP_CNT  8
#define MAX_UDPCEP_CNT  8
#endif

#define IP_TYPE_TCP  0
#define IP_TYPE_UDP  1

#ifdef R_TSIP_RX_HEADER_FILE
#define R_T4_DRIVER_RX_HASH_LENGTH R_TSIP_SHA256_HASH_LENGTH_BYTE_SIZE
#else
#define R_T4_DRIVER_RX_HASH_LENGTH 32
#endif

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
void timer_interrupt(void *pdata);

void wait_Xms(UH limit_time);
void reset_timer(void);
UH get_timer(void);

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
extern UB _myethaddr[][6];
#if   (BSP_CFG_RTOS_USED >= 1)
extern const H __tcpcepn;
extern const H __udpcepn;
#endif
extern int32_t callback_ether_regist(void);
#if defined (_T4_TEST)
extern H lan_read_for_test(UB lan_port_no, B **buf, H return_code);
#endif


/******************************************************************************
Private global variables and functions
******************************************************************************/
UH tcpudp_time_cnt;
UB tcpip_flag;
volatile UH wait_timer;
T4_STATISTICS t4_stat[2];
UB *err_buf_ptr;

#if   (BSP_CFG_RTOS_USED >= 1)
static uint32_t tcp_tsk_tbl[MAX_TCPCEP_CNT] = {0};
static uint32_t udp_tsk_tbl[MAX_UDPCEP_CNT] = {0};

static int32_t verify_cepn_cnt(void);
static ER sleep_task(ID cepid, uint32_t ip_type);
static uint32_t rtos_get_tid(void);
static ER rtos_slp_tsk(void);
static ER wakeup_task(ID cepid, uint32_t ip_type);
static ER rtos_wup_tsk(uint32_t tid);

extern ER		get_tid(ID *p_tskid);
extern ER		slp_tsk(void) ;
extern bool		sns_ctx(void);
extern ER		iwup_tsk(ID tskid);
extern ER		wup_tsk(ID tskid) ;
extern ER		iwup_tsk(ID tskid) ;
extern ER		rot_rdq(PRI tskpri);
#define TPRI_SELF		0
#endif  /* #if   (BSP_CFG_RTOS_USED >= 1) */

/******************************************************************************
Functions (API)
******************************************************************************/

ER lan_open(void)
{
    ER ret;
    ether_param_t   param;

#if   (BSP_CFG_RTOS_USED >= 1)
    /* verify tcp/udp param */
    if(0 != verify_cepn_cnt())
    {
        return -1;
    }
#endif /* #if   (BSP_CFG_RTOS_USED >= 1) */

    R_ETHER_Initial();
    callback_ether_regist();

    param.channel = ETHER_CHANNEL_0;
    R_ETHER_Control(CONTROL_POWER_ON, param);
#if (ETHER_CHANNEL_MAX >= 2)
    param.channel = ETHER_CHANNEL_1;
    R_ETHER_Control(CONTROL_POWER_ON, param);
#endif

    memset(&t4_stat[0], 0, sizeof(T4_STATISTICS));
    ret = R_ETHER_Open_ZC2(0, (const uint8_t *) & _myethaddr[0], false);
    if (ETHER_SUCCESS != ret)
    {
        return -1;
    }
#if (ETHER_CHANNEL_MAX >= 2)
    ret = R_ETHER_Open_ZC2(1, (const uint8_t *) & _myethaddr[1], false);
    if (ETHER_SUCCESS != ret)
    {
        return -1;
    }
#endif

    return 0;
}

ER lan_close(void)
{
    ether_param_t   param;

    R_ETHER_Close_ZC2(0);
#if (ETHER_CHANNEL_MAX >= 2)
    R_ETHER_Close_ZC2(1);
#endif

    param.channel = ETHER_CHANNEL_0;
    R_ETHER_Control(CONTROL_POWER_OFF, param);
#if (ETHER_CHANNEL_MAX >= 2)
    param.channel = ETHER_CHANNEL_1;
    R_ETHER_Control(CONTROL_POWER_OFF, param);
#endif

    return 0;
}

/******************************************************************************
Functions (Use definition function that called from T4 library)
******************************************************************************/

void ena_int(void)
{
    tcpip_flag = 1;
}

void dis_int(void)
{
    tcpip_flag = 0;
}


H rcv_buff_release(UB lan_port_no)
{
    /* This function is called when TCP/IP finished using receive buffer specified lan_read. */
    R_ETHER_Read_ZC2_BufRelease(lan_port_no);
    return 0;
}

UH tcpudp_get_time(void)
{
    return tcpudp_time_cnt;
}

void tcpudp_act_cyc(UB cycact)
{
    switch (cycact)
    {
        case 0:
            tcpip_flag = 0;
            CloseTimer();
            break;
        case 1:
            tcpip_flag = 1;
            OpenTimer();
            break;
        default:
            break;
    }
}

void lan_reset(UB lan_port_no)
{
    ether_param_t   param;

    if (ETHER_CHANNEL_MAX <= lan_port_no)
    {
        return;
    }

    if (0 == lan_port_no)
    {
        param.channel = ETHER_CHANNEL_0;
    }
#if (ETHER_CHANNEL_MAX >= 2)
    else //ETHER_CHANNEL_1
    {
        param.channel = ETHER_CHANNEL_1;
    }
#endif

    R_ETHER_Close_ZC2(lan_port_no);
    R_ETHER_Control(CONTROL_POWER_OFF, param);

    R_ETHER_Control(CONTROL_POWER_ON, param);
    R_ETHER_Open_ZC2(lan_port_no, (const uint8_t *)&_myethaddr[lan_port_no], false);
}

void udp_api_slp(ID cepid)
{
    /* If user uses "Real time OS", user may define "sleep task" here. */
#if   (BSP_CFG_RTOS_USED >= 1)
    ER ercd;
    ercd = sleep_task(cepid, IP_TYPE_UDP);
    if(ercd != E_OK)
    {
        /* WAIT_LOOP */
        while(1);
    }
#endif /* #if   (BSP_CFG_RTOS_USED >= 1) */
}

void udp_api_wup(ID cepid)
{
    /* If user uses "Real time OS", user may define "wake up task" here. */
#if   (BSP_CFG_RTOS_USED >= 1)
    ER ercd;
    ercd = wakeup_task(cepid, IP_TYPE_UDP);
    if(ercd != E_OK)
    {
        /* WAIT_LOOP */
        while(1);
    }
#endif /* #if   (BSP_CFG_RTOS_USED >= 1) */
}

void tcp_api_slp(ID cepid)
{
    /* If user uses "Real time OS", user may define "sleep task" here. */
#if   (BSP_CFG_RTOS_USED >= 1)
    ER ercd;
    ercd = sleep_task(cepid, IP_TYPE_TCP);
    if(ercd != E_OK)
    {
        /* WAIT_LOOP */
        while(1);
    }
#endif /* #if   (BSP_CFG_RTOS_USED >= 1) */
}

void tcp_api_wup(ID cepid)
{
    /* If user uses "Real time OS", user may define "wake up task" here. */
#if   (BSP_CFG_RTOS_USED >= 1)
    ER ercd;
    ercd = wakeup_task(cepid, IP_TYPE_TCP);
    if(ercd != E_OK)
    {
        /* WAIT_LOOP */
        while(1);
    }
#endif /* #if   (BSP_CFG_RTOS_USED >= 1) */
}

H lan_read(UB lan_port_no, B **buf)
{
    int32_t driver_ret;
    H return_code;
    B *data;

    driver_ret = R_ETHER_Read_ZC2(lan_port_no, (void **)buf);
    if (driver_ret > 0)
    {
        data = (B *)*buf;
        if(0 == memcmp(&data[6], &_myethaddr[lan_port_no], 6))
        {
            rcv_buff_release(lan_port_no);
            return_code = -1;
            return return_code;
        }
        t4_stat[lan_port_no].t4_rec_cnt++;
        t4_stat[lan_port_no].t4_rec_byte += (UW)driver_ret;
        return_code = (H)driver_ret;
    }
    else if (driver_ret == 0)
    {
        /* R_Ether_Read() returns "0" when receiving data is nothing */
        return_code = -1; // Return code "-1" notifies "no data" to T4.
    }
    else
    {
        /* R_Ether_Read() returns "negative values" when error occurred */
        return_code = -2; // Return code "-2" notifies "Ether controller disable" to T4.
//      return_code = -5; // Return code "-5" notifies "reset request" to T4.
//      return_code = -6; // Return code "-6" notifies "CRC error" to T4.
    }

#if defined (_T4_TEST)
    return_code = lan_read_for_test(lan_port_no, buf, return_code);
#endif

    return return_code;
}

H lan_write(UB lan_port_no, B *header , H header_len, B *data , H data_len)
{
    int32_t driver_ret;
    B *buf;
    uint16_t buf_size;
    uint16_t    framesize;

    driver_ret = R_ETHER_Write_ZC2_GetBuf(lan_port_no, (void **) & buf, &buf_size);
    if (ETHER_SUCCESS == driver_ret)
    {
        framesize = header_len + data_len;                                      /*data length calc.*/
        if (buf_size >= framesize)
        {
            memcpy(buf, header, header_len);
            memcpy(buf + header_len, data, data_len);
            if (framesize < ETHER_BUFSIZE_MIN)                                  /*under minimum*/
            {
                memset((buf + framesize), 0, (ETHER_BUFSIZE_MIN - framesize));  /*padding*/
                framesize = ETHER_BUFSIZE_MIN;                                  /*resize*/
            }
            else
            {
                /*nothing todo*/
            }
            driver_ret =  R_ETHER_Write_ZC2_SetBuf(lan_port_no, (uint16_t)framesize);
            if (ETHER_SUCCESS == driver_ret)
            {
                t4_stat[lan_port_no].t4_snd_cnt++;
                t4_stat[lan_port_no].t4_snd_byte += framesize;
                return 0;
            }
        }
    }
    return -5;
}

void report_error(UB lan_port_no, H err_code, UB *err_data)
{
    err_buf_ptr = err_data;

    switch (err_code)
    {
        case RE_LEN:
            t4_stat[lan_port_no].re_len_cnt++;
            break;
        case RE_NETWORK_LAYER:
            t4_stat[lan_port_no].re_network_layer_cnt++;
            break;
        case RE_TRANSPORT_LAYER:
            t4_stat[lan_port_no].re_transport_layer_cnt++;
            break;
        case RE_ARP_HEADER1:
            t4_stat[lan_port_no].re_arp_header1_cnt++;
            break;
        case RE_ARP_HEADER2:
            t4_stat[lan_port_no].re_arp_header2_cnt++;
            break;
        case RE_IP_HEADER1:
            t4_stat[lan_port_no].re_ip_header1_cnt++;
            break;
        case RE_IP_HEADER2:
            t4_stat[lan_port_no].re_ip_header2_cnt++;
            break;
        case RE_IP_HEADER3:
            t4_stat[lan_port_no].re_ip_header3_cnt++;
            break;
        case RE_IP_HEADER4:
            t4_stat[lan_port_no].re_ip_header4_cnt++;
            break;
        case RE_IP_HEADER5:
            t4_stat[lan_port_no].re_ip_header5_cnt++;
            break;
        case RE_IP_HEADER6:
            t4_stat[lan_port_no].re_ip_header6_cnt++;
            break;
        case RE_IP_HEADER7:
            t4_stat[lan_port_no].re_ip_header7_cnt++;
            break;
        case RE_IP_HEADER8:
            t4_stat[lan_port_no].re_ip_header8_cnt++;
            break;
        case RE_IP_HEADER9:
            t4_stat[lan_port_no].re_ip_header9_cnt++;
            break;
        case RE_TCP_HEADER1:
            t4_stat[lan_port_no].re_tcp_header1_cnt++;
            break;
        case RE_TCP_HEADER2:
            t4_stat[lan_port_no].re_tcp_header2_cnt++;
            break;
        case RE_UDP_HEADER1:
            t4_stat[lan_port_no].re_udp_header1_cnt++;
            break;
        case RE_UDP_HEADER2:
            t4_stat[lan_port_no].re_udp_header2_cnt++;
            break;
        case RE_UDP_HEADER3:
            t4_stat[lan_port_no].re_udp_header3_cnt++;
            break;
        case RE_ICMP_HEADER1:
            t4_stat[lan_port_no].re_icmp_header1_cnt++;
            break;
        case RE_IGMP_HEADER1:
            t4_stat[lan_port_no].re_igmp_header1_cnt++;
            break;
        case RE_IGMP_HEADER2:
            t4_stat[lan_port_no].re_igmp_header2_cnt++;
            break;
        case RE_DHCP_ILLEGAL:
            t4_stat[lan_port_no].re_dhcp_header1_cnt++;
            break;
        case RE_DHCP_SND_TIMEOUT:
            t4_stat[lan_port_no].re_dhcp_header2_cnt++;
            break;
        default:
            break;
    }
}


/******************************************************************************
Functions (Interrupt handler)
******************************************************************************/

void timer_interrupt(void *pdata)
{
    /* check LAN link stat */
    R_ETHER_LinkProcess(0);
#if (ETHER_CHANNEL_MAX >= 2)
    R_ETHER_LinkProcess(1);
#endif
    R_BSP_InterruptsEnable();

    if (tcpip_flag == 1)
    {
        tcpudp_time_cnt++;
        _process_tcpip();
    }

    /* for wait function */
    if (wait_timer < 0xFFFF)
    {
        wait_timer++;
    }
}

void lan_inthdr(void *ppram)
{
    R_BSP_InterruptsEnable();

    if (tcpip_flag == 1)
    {
        _process_tcpip();
    }
}

/******************************************************************************
Functions (Test function)
******************************************************************************/

void wait_Xms(UH limit_time)
{
    UH max;

    wait_timer = 0;
    max = limit_time / 10;

    /* WAIT_LOOP */
    while (wait_timer < max);
}

void reset_timer(void)
{
    wait_timer = 0;
}

UH get_timer(void)
{
    return wait_timer;
}

/******************************************************************************
Functions : random number generator
            (Used TSIP when the MCU has TSIP, otherwise XorShift method)
******************************************************************************/
void get_random_number(UB *data, UW len)
{
#ifdef R_TSIP_RX_HEADER_FILE
    e_tsip_err_t  tsip_ret;
    uint32_t org_random[4];
    UW loop_cnt = 0;
    UW out_len = 0;

    loop_cnt = len;
    memset( &org_random, 0, sizeof(org_random) );

    /* WAIT_LOOP */
    while ( loop_cnt > 0U )
    {
        if ( loop_cnt > 16 )
        {
            out_len = 16;
            loop_cnt -= 16;
        }
        else
        {
            out_len = len;
            loop_cnt = 0;
        }

        tsip_ret = R_TSIP_GenerateRandomNumber(&org_random[0]);

        memcpy(data, &org_random[0], out_len);

        data += out_len;

        if(TSIP_SUCCESS != tsip_ret)
        {
            /* WAIT_LOOP */
            while(1)
            {
                /* Processing at the time of the error */
                R_BSP_NOP();
            }
        }
    }
#else
    static uint32_t y = 2463534242;
    static uint32_t *z = (uint32_t *)&_myethaddr[0][2];
    uint32_t res;
    uint32_t lp;
    uint8_t *bPtr;

    if(z != NULL)
    {
        y ^= *z;
        z = NULL;
    }
    y += tcpudp_time_cnt;
    res = len / 4;
    /* WAIT_LOOP */
    for (lp = 0; lp < res; lp++)
    {
        y = y ^ (y << 13);
        y = y ^ (y >> 17);
        y = y ^ (y << 5);
        bPtr = (uint8_t*) & y;
#if __LIT
        *((uint32_t *)data) = (*(bPtr + 3) << 24) | (*(bPtr + 2) << 16) | (*(bPtr + 1) << 8) | *(bPtr + 0);
#else
        *((uint32_t *)data) = y;
#endif
        data += 4;
    }
    y = y ^ (y << 13);
    y = y ^ (y >> 17);
    y = y ^ (y << 5);
    res = (uint32_t)len % 4;
    bPtr = (uint8_t*) & y;
    switch (res)
    {
        case 3:
#if __LIT
            *data++ = bPtr[3];
            *data++ = bPtr[2];
            *data++ = bPtr[1];
#else
            *data++ = bPtr[0];
            *data++ = bPtr[1];
            *data++ = bPtr[2];
#endif
            break;

        case 2:
#if __LIT
            *data++ = bPtr[3];
            *data++ = bPtr[2];
#else
            *data++ = bPtr[0];
            *data++ = bPtr[1];
#endif
            break;

        case 1:
#if __LIT
            *data++ = bPtr[3];
#else
            *data++ = bPtr[0];
#endif
            break;

        default:
            /* no op */
            break;
    }
#endif
}

/******************************************************************************
Functions : hash value generator
            (Used SHA256 by TSIP when the MCU has TSIP, or XOR calculation for random number)
******************************************************************************/
void get_hash_value(UB lan_port_no, UB *message, UW message_len, UB **hash, UW *hash_len)
{
    static UB hash_result[ETHER_CHANNEL_MAX][R_T4_DRIVER_RX_HASH_LENGTH];
    UW hash_result_len = R_T4_DRIVER_RX_HASH_LENGTH;

#ifdef R_TSIP_RX_HEADER_FILE
    e_tsip_err_t tsip_ret;
    tsip_sha_md5_handle_t sha256_handle; /* TSIP SHA256 handle */
#else
    UW hash_result_index = 0;
    UW loop_cnt = 0;
    UW hash_block_cnt = message_len / R_T4_DRIVER_RX_HASH_LENGTH;
    UW hash_block_odd = message_len % R_T4_DRIVER_RX_HASH_LENGTH;
    UB random_value[R_T4_DRIVER_RX_HASH_LENGTH];
#endif

    if(ETHER_CHANNEL_MAX < lan_port_no)
    {
        /* WAIT_LOOP */
        while(1)
        {
        R_BSP_NOP();    /* Channel error */
        }
    }

#ifdef R_TSIP_RX_HEADER_FILE
    /* SHA256 */
    tsip_ret = R_TSIP_Sha256Init(&sha256_handle);
    if (TSIP_SUCCESS == tsip_ret)
    {
        tsip_ret = R_TSIP_Sha256Update(&sha256_handle, message, message_len);
    }
    if (TSIP_SUCCESS == tsip_ret)
    {
        tsip_ret = R_TSIP_Sha256Final(&sha256_handle, &hash_result[lan_port_no][0], &hash_result_len);
    }
    if (TSIP_SUCCESS != tsip_ret)
    {
        while (1)
        {
            R_BSP_NOP();    /* Processing at the time of the error */
        }
    }
#else
    memset(hash_result, 0x0, sizeof(hash_result));
    
    if (message_len >= R_T4_DRIVER_RX_HASH_LENGTH)
    {
        /* XOR calculation to self by R_T4_DRIVER_RX_HASH_LENGTH */
        /* WAIT_LOOP */
        for (loop_cnt = 0; loop_cnt < hash_block_cnt; loop_cnt++)
        {
            for (hash_result_index = 0; hash_result_index < R_T4_DRIVER_RX_HASH_LENGTH; hash_result_index++)
            {
                hash_result[lan_port_no][hash_result_index] ^= message[(R_T4_DRIVER_RX_HASH_LENGTH * loop_cnt) + hash_result_index];
            }
        }
    }

    /* XOR calculation to self for fraction */
    /* WAIT_LOOP */
    for (hash_result_index = 0; hash_result_index < hash_block_odd; hash_result_index++)
    {
        hash_result[lan_port_no][hash_result_index] ^= message[(R_T4_DRIVER_RX_HASH_LENGTH * hash_block_cnt) + hash_result_index];
    }

    /* Get random value */
    get_random_number(&random_value[0], R_T4_DRIVER_RX_HASH_LENGTH - hash_block_odd);
    
    /* XOR calculation by random value */
    /* WAIT_LOOP */
    for (hash_result_index = hash_block_odd; hash_result_index < R_T4_DRIVER_RX_HASH_LENGTH; hash_result_index++)
    {
        hash_result[lan_port_no][hash_result_index] ^= random_value[hash_result_index - hash_block_odd];
    }
#endif

    *hash = &hash_result[lan_port_no][0];
    *hash_len = hash_result_len;
}

/***********************************************************************************************************************
* Function Name: lan_check_link
* Description  : MSS setting function
* Arguments    : channel
*                  RJ45 interface,other
* Return Value : E_OK fixed
***********************************************************************************************************************/
H lan_check_link(UB lan_port_no)
{
    H   res;

    if(ETHER_SUCCESS == R_ETHER_CheckLink_ZC(lan_port_no))
    {
        res = 1;
    }
    else
    {
        res = 0;
    }

    return res;
}

#if   (BSP_CFG_RTOS_USED >= 1)
static int32_t verify_cepn_cnt(void)
{
    int32_t ret;
    if((__tcpcepn > MAX_TCPCEP_CNT) || (__udpcepn > MAX_UDPCEP_CNT))
    {
        /* CHeck NG */
        ret = -1;
    }
    else
    {
        /* CHeck OK */
        ret = 0;
    }
    return ret;
}

static ER sleep_task(ID cepid, uint32_t ip_type)
{
    if(ip_type == IP_TYPE_TCP)
    {
        tcp_tsk_tbl[cepid - 1] = rtos_get_tid();
    }
    else
    {
        udp_tsk_tbl[cepid - 1] = rtos_get_tid();
    }
    return rtos_slp_tsk();
}

/*
 * get current task id/handle
 */
static uint32_t rtos_get_tid(void)
{
#if   BSP_CFG_RTOS_USED == 1    // FreeRTOS
    TaskHandle_t tid;

    tid = xTaskGetCurrentTaskHandle();
    return (uint32_t) tid;

#elif BSP_CFG_RTOS_USED == 4    // Renesas RI600V4 & RI600PX
    ID tid;

    get_tid(&tid);
    return (uint32_t) tid;
#else
    return 0;
#endif
}

/*
 * sleep current task
 */
static ER rtos_slp_tsk(void)
{
#if   BSP_CFG_RTOS_USED == 1    // FreeRTOS
    vTaskSuspend(NULL);
    return E_OK;

#elif BSP_CFG_RTOS_USED == 4 // wata 4    // Renesas RI600V4 & RI600PX
    if(true == sns_ctx()) {
    	return E_OK;
    } else {
        return slp_tsk();
    }

#else
    return E_OK;  /* nothing to do */
#endif
}


static ER wakeup_task(ID cepid, uint32_t ip_type)
{
    uint32_t tid;

    if(ip_type == IP_TYPE_TCP)
    {
        tid = tcp_tsk_tbl[cepid - 1];
    }
    else
    {
        tid = udp_tsk_tbl[cepid - 1];
    }
    return rtos_wup_tsk(tid);
}

/*
 * wake-up task by id/handle
 */
static ER rtos_wup_tsk(uint32_t tid)
{
#if   BSP_CFG_RTOS_USED == 1    // FreeRTOS
    if(0 == tid)
    {
        return E_ID;
    }
    if(0 == (get_psw() & 0x20000))
    {
        xTaskResumeFromISR((TaskHandle_t) tid);
    }
    else
    {
        vTaskResume((TaskHandle_t) tid);
    }
    return E_OK;

#elif BSP_CFG_RTOS_USED == 4    // Renesas RI600V4 & RI600PX
    ER ret;

    if(0 == tid)
    {
        return E_ID;
    }
    if(true == sns_ctx())
    {
        return iwup_tsk((ID) tid);
    }
    else
    {
        ret = wup_tsk((ID) tid);
        if(ret == E_OK)
        {
            return rot_rdq(TPRI_SELF);  /* dispatch task to user tcp/udp */
        }
        else
        {
            return ret;
        }
    }
#else
    return E_OK;  /* nothing to do */
#endif
}
#undef BSP_CFG_RTOS_USED
#define BSP_CFG_RTOS_USED 0
#endif /* #if   (BSP_CFG_RTOS_USED >= 1) */
