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

/*******************************************************************************
* File Name     : dhcp_client.c
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 21.06.2010 1.00    First Release
*               : 30.08.2011 1.01    Clean up source code
*               : 01.04.2014 2.00    Release for V.2.00
*               : 10.12.2018 2.08    Release for V.2.08
*               : 20.05.2019 2.09    Release for V.2.09
******************************************************************************/

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "r_t4_itcpip.h"
#include "r_ether_rx_if.h"
#include "r_sys_time_rx_if.h"
#include "dhcp_client.h"
#include "r_t4_rx_config.h"

static UB guc_event[T4_CFG_SYSTEM_CHANNEL_NUMBER];
static DHCP* gpt_dhcp[T4_CFG_SYSTEM_CHANNEL_NUMBER];

 
/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
******************************************************************************/
extern ER		slp_tsk(void) ;
extern ER		dly_tsk(UW) ;
extern int dhcp_accept_flg;
/* static variables */
static st_cep_t cep[CEP_NUM];
static UB guc_event[T4_CFG_SYSTEM_CHANNEL_NUMBER];
static DHCP* gpt_dhcp[T4_CFG_SYSTEM_CHANNEL_NUMBER];

/******************************************************************************
* Function Name     : dhcp_client_func
* Description       : echo server main function.
* Argument          : none
* Return Value      : none
******************************************************************************/

void dhcp_client_func(void)
{
    ID cepid;
    ID repid;
    UB interface;
    ER ercd;
    uint32_t i;
    uint32_t k;
    uint32_t n;
    T_IPV4EP    dst_addr2;
    /* initialize cep status */
    /* WAIT_LOOP */
    for (i = 0; i < CEP_NUM; i++)
    {
        cep[i].status = T4_CLOSED;
    }

    /* refer to tcp_crep[0] */
    n = 0;

    /* WAIT_LOOP */
    while (n < CEP_NUM)
    {
    	int16_t pstatus = phy_get_link_status(0);
    	//int16_t pstatus1 = phy_get_link_status(1);

        /* dhcp use*/
        if(1 == _t4_dhcp_enable)
        {
            /* check all connections */
            /* WAIT_LOOP */
            for (i = 0; i < _t4_channel_num; i++)
            {
                interface = i;
                /* t4 reset request */
                if (DHCP_EV_PLEASE_RESET == guc_event[interface])
                {
                    /* reset callback event */
                    guc_event[interface] = 0;
#if defined(DEBUG_PRINT)
                    printf("main:call tcpudp_reset(channel:%d)\n", interface);
#endif /*#if defined(DEBUG_PRINT)*/
                    /* reset DHCP use interface */
                    tcpudp_reset(interface);

                    /* reset application data same as interface. */
                    /* WAIT_LOOP */
                    for (k = 0; k < CEP_NUM; k++)
                    {
                        if (interface == tcp_ccep[k + CEPID_BEGIN - 1].lan_port_number)
                        {
                            memset(&cep[k], 0, sizeof(st_cep_t));
                            cep[k].status = T4_CLOSED;
                        }
                    }
                }
            }
        }
		 dly_tsk(1);

    }
  return;
}
#if defined(DEBUG_PRINT)
    uint8_t*    ev_tbl[] =
    {
        "ETHER_EV_LINK_OFF",
        "ETHER_EV_LINK_ON",
        "ETHER_EV_COLLISION_IP",
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
        "DHCP_EV_LEASE_IP",
        "DHCP_EV_LEASE_OVER",
        "DHCP_EV_INIT",
        "DHCP_EV_INIT_REBOOT",
        "DHCP_EV_APIPA",
        "DHCP_EV_NAK",
        "DHCP_EV_FATAL_ERROR",
        "DHCP_EV_PLEASE_RESET"
    };
#endif /*#if defined(DEBUG_PRINT)*/

/******************************************************************************
* Function Name     : system_callback
* Description       : Ethernet callback.
* Argument          : UB        channel ;    RJ45 interface
*                   : UW        eventid ;    Event code
*                   : VP        param   ;    Parameter block
* Return Value      : ER                ;    always 0 (not in use)
******************************************************************************/
ER system_callback(UB channel, UW eventid, VP param)
{

    printf("^^>>>user_cb<<< ch:%d,eventID = %s\n", channel, ev_tbl[eventid]);
    guc_event[channel] = eventid;
    switch(eventid)
    {
        case ETHER_EV_LINK_OFF:
        {
            /* Do Nothing. */
        }
        break;

        case ETHER_EV_LINK_ON:
        {
            /* Do Nothing. */
        }
        break;

        case ETHER_EV_COLLISION_IP:
        {
            /* Do Nothing. */
        }
        break;

        case DHCP_EV_LEASE_IP:
        {
            /* cast from VP to DHCP* */
            gpt_dhcp[channel] = (DHCP*)param;
#if defined(DEBUG_PRINT)
            printf("DHCP.ipaddr[4]   %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->ipaddr[0], gpt_dhcp[channel]->ipaddr[1],
                   gpt_dhcp[channel]->ipaddr[2], gpt_dhcp[channel]->ipaddr[3]);
            printf("DHCP.maskaddr[4] %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->maskaddr[0], gpt_dhcp[channel]->maskaddr[1],
                   gpt_dhcp[channel]->maskaddr[2], gpt_dhcp[channel]->maskaddr[3]);
            printf("DHCP.gwaddr[4]   %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->gwaddr[0], gpt_dhcp[channel]->gwaddr[1],
                   gpt_dhcp[channel]->gwaddr[2], gpt_dhcp[channel]->gwaddr[3]);
            printf("DHCP.dnsaddr[4]  %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->dnsaddr[0], gpt_dhcp[channel]->dnsaddr[1],
                   gpt_dhcp[channel]->dnsaddr[2], gpt_dhcp[channel]->dnsaddr[3]);
            printf("DHCP.dnsaddr2[4] %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->dnsaddr2[0], gpt_dhcp[channel]->dnsaddr2[1],
                   gpt_dhcp[channel]->dnsaddr2[2], gpt_dhcp[channel]->dnsaddr2[3]);
            printf("DHCP.macaddr[6]  %02X:%02X:%02X:%02X:%02X:%02X\n",
                   gpt_dhcp[channel]->macaddr[0],  gpt_dhcp[channel]->macaddr[1],  gpt_dhcp[channel]->macaddr[2],
                   gpt_dhcp[channel]->macaddr[3],  gpt_dhcp[channel]->macaddr[4],  gpt_dhcp[channel]->macaddr[5]);
            printf("DHCP.domain[%d] %s\n", strlen(gpt_dhcp[channel]->domain), gpt_dhcp[channel]->domain);
            printf("\n");
            dhcp_accept_flg = 1;

#endif /*#if defined(DEBUG_PRINT)*/
        }
        break;

        case DHCP_EV_LEASE_OVER:
        {
            /* Do Nothing. */
        }
        break;

        case DHCP_EV_INIT:
        {

            /* Do Nothing. */
        }
        break;

        case DHCP_EV_INIT_REBOOT:
        {
            /* Do Nothing. */
        }
        break;

        case DHCP_EV_APIPA:
        {
            /* cast from VP to DHCP* */
            gpt_dhcp[channel] = (DHCP*)param;
#if defined(DEBUG_PRINT)
            printf("DHCP.ipaddr[4]   %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->ipaddr[0], gpt_dhcp[channel]->ipaddr[1],
                   gpt_dhcp[channel]->ipaddr[2], gpt_dhcp[channel]->ipaddr[3]);
            printf("DHCP.maskaddr[4] %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->maskaddr[0], gpt_dhcp[channel]->maskaddr[1],
                   gpt_dhcp[channel]->maskaddr[2], gpt_dhcp[channel]->maskaddr[3]);
            printf("DHCP.gwaddr[4]   %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->gwaddr[0], gpt_dhcp[channel]->gwaddr[1],
                   gpt_dhcp[channel]->gwaddr[2], gpt_dhcp[channel]->gwaddr[3]);
            printf("DHCP.dnsaddr[4]  %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->dnsaddr[0], gpt_dhcp[channel]->dnsaddr[1],
                   gpt_dhcp[channel]->dnsaddr[2], gpt_dhcp[channel]->dnsaddr[3]);
            printf("DHCP.dnsaddr2[4] %d.%d.%d.%d\n",
                   gpt_dhcp[channel]->dnsaddr2[0], gpt_dhcp[channel]->dnsaddr2[1],
                   gpt_dhcp[channel]->dnsaddr2[2], gpt_dhcp[channel]->dnsaddr2[3]);
            printf("DHCP.macaddr[6]  %02X:%02X:%02X:%02X:%02X:%02X\n",
                   gpt_dhcp[channel]->macaddr[0],  gpt_dhcp[channel]->macaddr[1],  gpt_dhcp[channel]->macaddr[2],
                   gpt_dhcp[channel]->macaddr[3],  gpt_dhcp[channel]->macaddr[4],  gpt_dhcp[channel]->macaddr[5]);
            printf("DHCP.domain[%d] %s\n", strlen(gpt_dhcp[channel]->domain), gpt_dhcp[channel]->domain);
            printf("\n");
#endif /*#if defined(DEBUG_PRINT)*/
        }
        break;

        case DHCP_EV_NAK:
        {
            /* Do Nothing. */
        }
        break;

        case DHCP_EV_FATAL_ERROR:
        {
            /* Do Nothing. */
        }
        break;

        case DHCP_EV_PLEASE_RESET:
        {
            /* Do Nothing. */
        }
        break;

        default:
        {
            /* Do Nothing. */
        }
        break;
    }
    return 0;
}
