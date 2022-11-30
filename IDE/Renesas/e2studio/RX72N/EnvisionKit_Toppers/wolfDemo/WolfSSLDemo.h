/*
 * WolfSSLDemo.h
 *
 *  Created on: 2022/11/06
 *      Author: nekom
 */

#ifndef WOLFSSLDEMO_H_
#define WOLFSSLDEMO_H_


#define DEBUG_PRINT
#define SERVER_TEST
#define ETHER_TASK

void main(void);
void init_ether();

/******************************************************************************
Typedef definitions
******************************************************************************/

extern ER		dly_tsk(UW) ;
extern void dhcp_client_func(void);
extern void startw(void);
extern void waisem_ether_wrapper();
extern void sigsem_ether_wrapper();
extern void timer_interrupt(void *pdata);
extern void cmt_isr_common2 (uint32_t channel);
extern void wolfSSL_init(void);
extern void wolfSSL_TLS_client_Wrapper() ;
extern void wolfSSL_TLS_server_Wrapper() ;
extern void timeTick(void *pdata);

#define LED_CTL(x)  \
		PORT4.PODR.BYTE = x;	\
		PORT4.PDR.BYTE = 0x01;

#endif /* WOLFSSLDEMO_H_ */
