/*
 * dhcp_chk_evt.c
 *
 *  Created on: 2022/12/08
 *      Author: 421003
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "r_t4_itcpip.h"
#include "r_ether_rx_if.h"
#include "r_sys_time_rx_if.h"
#include "r_t4_rx_config.h"
extern const UB _t4_dhcp_enable;
/* event flg global */
extern UB	dhcp_evt ;

void dhcp_check(void);
void print_dhcp(VP param);

#define DHCP_ENABEL        (1)
#define IF_CH_NUMBER       (0)

/* DHCP Reset Event Check */
void dhcp_check(void)
{

	if(DHCP_ENABEL == _t4_dhcp_enable && dhcp_evt == DHCP_EV_PLEASE_RESET){
        tcpudp_reset(IF_CH_NUMBER);
        dhcp_evt = 0;
	}

	return;

}


void print_dhcp(VP param)
{
	DHCP* dhcp_data = (DHCP*)param;
    printf("Accept DHCP.ipaddr[4]   %d.%d.%d.%d\n",dhcp_data->ipaddr[0], dhcp_data->ipaddr[1],
           dhcp_data->ipaddr[2], dhcp_data->ipaddr[3]);
    printf("Accept DHCP.maskaddr[4] %d.%d.%d.%d\n",dhcp_data->maskaddr[0], dhcp_data->maskaddr[1],
           dhcp_data->maskaddr[2], dhcp_data->maskaddr[3]);
    printf("Accept DHCP.gwaddr[4]   %d.%d.%d.%d\n",dhcp_data->gwaddr[0], dhcp_data->gwaddr[1],
           dhcp_data->gwaddr[2], dhcp_data->gwaddr[3]);
    printf("Accept DHCP.dnsaddr[4]  %d.%d.%d.%d\n",dhcp_data->dnsaddr[0], dhcp_data->dnsaddr[1],
           dhcp_data->dnsaddr[2], dhcp_data->dnsaddr[3]);
    printf("Accept DHCP.dnsaddr2[4] %d.%d.%d.%d\n",dhcp_data->dnsaddr2[0], dhcp_data->dnsaddr2[1],
           dhcp_data->dnsaddr2[2], dhcp_data->dnsaddr2[3]);
    printf("Accept DHCP.macaddr[6]  %02X:%02X:%02X:%02X:%02X:%02X\n",dhcp_data->macaddr[0],  dhcp_data->macaddr[1],  dhcp_data->macaddr[2],
           dhcp_data->macaddr[3],  dhcp_data->macaddr[4],  dhcp_data->macaddr[5]);
    printf("Accept DHCP.domain[%d] %s\n", strlen(dhcp_data->domain), dhcp_data->domain);
    printf("\n");
    return;
}

