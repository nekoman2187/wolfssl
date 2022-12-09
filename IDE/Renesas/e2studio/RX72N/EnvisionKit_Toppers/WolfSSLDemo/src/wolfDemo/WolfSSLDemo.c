/***********************************************************************
*
*  FILE        : WolfSSLDemo.c
*  DATE        : 2022-05-17
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "r_t4_itcpip.h"
#include "r_sys_time_rx_if.h"
#include "Pin.h"
#include <stdio.h>
#include <stdlib.h>
#include "r_smc_entry.h"
#include "platform.h"
#include "r_cmt_rx_if.h"
#include "r_t4_itcpip.h"
#include "r_t4_rx_config.h"
#include "Pin.h"
#include "r_ether_rx_pinset.h"
#include "platform.h"
#include "WolfSSLDemo.h"
#define SSL_SERVER
//#define ETHER_TASK

static int dhcp_accept_flg = 0;
static UW tcpudp_work[14800] = {0};
UB	dhcp_evt = 0;

void main(void)
{
/*Toopers start function */
  startw();
}

void timer_int_Wrapper() {
#ifndef ETHER_TASK
	//cmt1_isr();
#endif
 }

 void timer_cm2_int_Wrapper() {
	 int du = 0;
	 timeTick((void *)&du);
 }
extern bool		sns_ctx(void);

void ether_int_Wrapper() {
    R_BSP_InterruptControl(BSP_INT_SRC_AL1_EDMAC0_EINT0, BSP_INT_CMD_CALL_CALLBACK, FIT_NO_PTR);
}
void taskEther(intptr_t exinf) {
	int dhcp_cnt = 0;
	bool flg = false;
	while(1) {
		if (flg == false) {
			waisem_ether_wrapper();
			flg = true;
		}
		dhcp_check();
		dly_tsk(1);

	}

}
void taskNetWork(intptr_t exinf) {
	UB ctl = 0;
	UW i = 0;
	while(1) {
		if(!(i % 10)) {
			ctl = ctl ? 0 : 1;
		}
		LED_CTL(ctl)
		i++;
#ifdef ETHER_TASK
		cmt1_isr();
#endif
		dly_tsk(1);

	}

}
#define FREQ 10000 /* Hz */
extern void timeTick(void *pdata);

void taskDemoWolf(intptr_t exinf) {
	uint32_t channel;
	wolfSSL_init();
	if(!init_ether()) return ;
    R_CMT_CreatePeriodic(FREQ, &timeTick, &channel);
    ICU.SLIBXR128.BYTE = 1; //select B

	sigsem_ether_wrapper();
	while(1) {
		dly_tsk(10);
		if (dhcp_accept_flg == 1) {
			 dly_tsk(100);
#ifdef SSL_SERVER
			 wolfSSL_TLS_server_Wrapper();
#else
			 wolfSSL_TLS_client_Wrapper();
#endif
		}
	}

}

bool init_ether() {
    ER   ercd;
    W    size;
    sys_time_err_t systime_ercd;
    systime_ercd = R_SYS_TIME_Open();
    if (systime_ercd != SYS_TIME_SUCCESS)
    {
        printf("init_ether R_SYS_TIME_Open　Error%d \n",systime_ercd);
        return false;
    }
    R_Pins_Create();

    ercd = lan_open();
    if (ercd != E_OK) {
        printf("lan_open 　Error%d \n",ercd);
        return false;
    }

    size = tcpudp_get_ramsize();
    if (size > (sizeof(tcpudp_work)))
    {
        printf("tcpudp_get_ramsize size　over %d \n",size);
        return false;
    }
    ercd = tcpudp_open(tcpudp_work);
    if (ercd != E_OK)
    {
        printf("tcpudp_open Open　Error %d \n",ercd);
        return false;
    }
    return true;
}

ER system_callback(UB channel, UW eventid, VP param)
{
    printf("Network callback accept channel=%d,EventNo=%d \n",channel,eventid);
    dhcp_evt = eventid;
    switch(eventid)
    {
        case ETHER_EV_LINK_OFF:
        {
            printf("DHCP Event Accept ETHER_EV_LINK_OFF\n");
        }
        break;
        case ETHER_EV_LINK_ON:
        {
            printf("DHCP Event Accept ETHER_EV_LINK_ON\n");
        }
        break;
        case ETHER_EV_COLLISION_IP:
        {
            printf("DHCP Event Accept ETHER_EV_COLLISION_IP\n");
        }
        break;
        case DHCP_EV_LEASE_IP:
        {
            printf("DHCP Event Accept DHCP_EV_LEASE_IP\n");
            print_dhcp(param);
            dhcp_accept_flg = 1;
        }
        break;

        case DHCP_EV_LEASE_OVER:
        {
            printf("DHCP Event Accept DHCP_EV_LEASE_OVER\n");
        }
        break;

        case DHCP_EV_INIT:
        {

            printf("DHCP Event Accept DHCP_EV_INIT\n");
        }
        break;

        case DHCP_EV_INIT_REBOOT:
        {
            printf("DHCP Event Accept DHCP_EV_INIT_REBOOT\n");
        }
        break;

        case DHCP_EV_APIPA:
        {
            printf("DHCP Event Accept DHCP_EV_LEASE_IP\n");
            print_dhcp(param);
            dhcp_accept_flg = 1;
        }
        break;

        case DHCP_EV_NAK:
        {
            printf("DHCP Event Accept DHCP_EV_NAK\n");
        }
        break;

        case DHCP_EV_FATAL_ERROR:
        {
            printf("DHCP Event Accept DHCP_EV_FATAL_ERROR\n");
        }
        break;

        case DHCP_EV_PLEASE_RESET:
        {
            printf("DHCP Event Accept DHCP_EV_PLEASE_RESET\n");
        }
        break;

        default:
        {
            printf("DHCP Event Accept undefined\n");
        }
        break;
    }
    return 0;

}
