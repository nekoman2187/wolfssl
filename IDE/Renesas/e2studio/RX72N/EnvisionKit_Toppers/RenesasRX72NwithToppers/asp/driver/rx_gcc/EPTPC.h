/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2017- by Hisashi Hata, JAPAN
 *
 * The above copyright holders grant permission gratis to use,
 * duplicate, modify, or redistribute (hereafter called use) this
 * software (including the one made by modifying this software),
 * provided that the following four conditions (1) through (4) are
 * satisfied.
 *
 * (1) When this software is used in the form of source code, the above
 *     copyright notice, this use conditions, and the disclaimer shown
 *     below must be retained in the source code without modification.
 *
 * (2) When this software is redistributed in the forms usable for the
 *     development of other software, such as in library form, the above
 *     copyright notice, this use conditions, and the disclaimer shown
 *     below must be shown without modification in the document provided
 *     with the redistributed software, such as the user manual.
 *
 * (3) When this software is redistributed in the forms unusable for the
 *     development of other software, such as the case when the software
 *     is embedded in a piece of equipment, either of the following two
 *     conditions must be satisfied:
 *
 *   (a) The above copyright notice, this use conditions, and the
 *       disclaimer shown below must be shown without modification in
 *       the document provided with the redistributed software, such as
 *     the user manual.
 *
 *   (b) How the software is to be redistributed must be reported to the
 *       TOPPERS Project according to the procedure described
 *       separately.
 *
 * (4) The above copyright holders and the TOPPERS Project are exempt
 *     from responsibility for any type of damage directly or indirectly
 *     caused from the use of this software and are indemnified by any
 *     users or end users of this software from any and all causes of
 *     action whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 * THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 * TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 * INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */


#ifndef RX_GCC_DRIVER_EPTPC_H
#define RX_GCC_DRIVER_EPTPC_H

#include <driver/rx_gcc/EPTPC_reg.h>

#define EPTPC_TIMEOUT -1
#define EPTPC_UN_INIT -2
#define EPTPC_OK 1

typedef struct eptp_init_cons_t {
  uint32_t ipclk_conf;
  uint32_t stca_sel;
} PTPSYS;

typedef struct eptp_port_conf_t{
  uint32_t ptp_mode;
  uint32_t self_clkid[2];
  uint32_t master_clkid[2];
  uint32_t grand_master_clkid[2];
  uint32_t master_portnum;
  uint16_t inport_delay;   //for TSLATR INGP
  uint16_t outport_delay;  //for TSLATR EGP
} PTP_PORT;


typedef struct eptp_port_init_t {
  PTPSYS *sys;
  PTP_PORT *port;
} PTPINI;

typedef struct PTPCLK_T{
  uint32_t nano_sec;
  uint32_t sec_l;
  uint32_t sec_h;
}PTPCLK;

//Port mode setting
#define EPTPC_MODE_P2P 0x1
#define EPTPC_MODE_E2E 0x2
#define EPTPC_MODE_MASTER 0x4
#define EPTPC_MODE_SLAVE 0x8
#define EPTPC_MODE_PORT0 0x10
#define EPTPC_MODE_PORT1 0x20
//target depend function
void eptpc_target_config(uint8_t* mac_ad, uint32_t ipclk_conf, uint32_t stca_sel, uint32_t port_mode);
void eptpc_init(PTPINI* pini);
ER ptp_sync_start(PTPINI* pini);

//SYNC timeout
#define EPTPC_CFG_SYNC_TOUT (0x03938700)

#define PTP_CFG_ANNOUNCE_FLAG 0x0
#define PTP_CFG_SYNC_FLAG 0x0
#define PTP_CFG_DYRQFR_FLAG 0x0
#define PTP_CFG_DYRPFR_FLAG 0x0
//transmmission interval
#define PTP_CFG_TRANCE_ANNOUNCE_INTERVAL 0 //1 sec
#define PTP_CFG_TRANCE_SYNC_INTERVAL 0xFE //250msex
#define PTP_CFG_TRANCE_DREQ_INTERVAL 0x5 //32 sec
//current clock param
#define PTP_CFG_CUR_UTC_OFFSET 10
#define PTP_CFG_TIME_SOURCE

//grandmaster clock property config (TBD, currently dummy)
#define PTP_CFG_GM_PRIORITY_1 0x0
#define PTP_CFG_GM_PRIORITY_2 0x0
#define PTP_CFG_GM_CLKQUALITY 0x0
#define PTP_CFG_GM_PORTID_U 0x100203FF
#define PTP_CFG_GM_PORTID_L 0xFE040506

//PTP define
#define CURRENT_UTC_OFFSET (0x0008) /* approx. 1588 spec AnnexB B.2 */
#define PTP2NTP_OFFSET (2208988800) /* 2,208,988,800 sec */
#define NTP_SEC (3668572800) /* NTP(Network Time Protocol) second, 2016/03/31 08:00:00, 3,668,572,800 sec */
#define PTP_SEC (NTP_SEC - PTP2NTP_OFFSET + CURRENT_UTC_OFFSET) /* PTP second */
//timeSource enumeration
#define TIME_SOURCE_ATOMIC_CLK 0x10
#define TIME_SOURCE_GPS 0x20
#define TIME_SOURCE_TERRESTRIAL_RADIO 0x30
#define TIME_SOURCE_PTP 0x40
#define TIME_SOURCE_NTP 0x50
#define TIME_SOURCE_HAND_SET 0x60
#define TIME_SOURCE_OTHER 0x90
#define TIME_SOURCE_INTERNAL_OSCILLATOR 0xA0

//Ethertype define (Annex F.2)
#define PTP_ETHERTYPE 0x88F7
//PTP MAC address define(Annex F.3)
//All except peer delay mechanism messages
#define AE_PDELAY_MECHANISM_MSG_U 0x00011B19
#define AE_PDELAY_MECHANISM_MSG_L 0x00000000
//Peer delay mechanism messages
#define PDELAY_MECHANISM_MSG_U 0x000180C2
#define PDELAY_MECHANISM_MSG_L 0x0000000E
//PTP UDP IP define(Annex D.3)
//PTP-primary
#define IPV4_PTP_PRIMARY  0xE0000181 //224.0.1.129
//PTP-pdelay
#define IPV4_PTP_PDELAY 0xE000006B //224.0.0.107
//PTP TOS TTL(Annex D.4)
#define UDP_PTP_EVENT_TOS 0x0
#define UDP_PTP_GENERAL_TOS 0x0
//udp pdelay ttl (Annex D.3)
#define UDP_PTP_PDELAY_TTL 0x1
//udp primary ttl
#define UDP_PTP_PRIMARY_TTL 0x80 //128
//udp port number(annex D.2)
#define UDP_PTP_EVENT_PORT_NUM 319
#define UDP_PTP_MCAST_PORT_NUM 320

//Time stamp delay parameter(TSLATR config)
#define TSLATR_EGP_MII100_STCA20 590
#define TSLATR_EGP_MII100_STCA25 625
#define TSLATR_EGP_MII100_STCA50 695
#define TSLATR_EGP_MII100_STCA100 730
#define TSLATR_EGP_MII10_STCA20 7430
#define TSLATR_EGP_MII10_STCA25 7465
#define TSLATR_EGP_MII10_STCA50 7535
#define TSLATR_EGP_MII10_STCA100 7570
#define TSLATR_EGP_RMII100_STCA20 770
#define TSLATR_EGP_RMII100_STCA25 805
#define TSLATR_EGP_RMII100_STCA50 875
#define TSLATR_EGP_RMII100_STCA100 910
#define TSLATR_EGP_RMII10_STCA20 9230
#define TSLATR_EGP_RMII10_STCA25 9265
#define TSLATR_EGP_RMII10_STCA50 9335
#define TSLATR_EGP_RMII10_STCA100 9370
#define TSLATR_INGP_MII100_STCA20 980
#define TSLATR_INGP_MII100_STCA25 945
#define TSLATR_INGP_MII100_STCA50 875
#define TSLATR_INGP_MII100_STCA100 840
#define TSLATR_INGP_MII10_STCA20 8180
#define TSLATR_INGP_MII10_STCA25 8145
#define TSLATR_INGP_MII10_STCA50 8075
#define TSLATR_INGP_MII10_STCA100 8015
#define TSLATR_INGP_RMII100_STCA20 1060
#define TSLATR_INGP_RMII100_STCA25 1025
#define TSLATR_INGP_RMII100_STCA50 955
#define TSLATR_INGP_RMII100_STCA100 920
#define TSLATR_INGP_RMII10_STCA20 8980
#define TSLATR_INGP_RMII10_STCA25 8945
#define TSLATR_INGP_RMII10_STCA50 8875
#define TSLATR_INGP_RMII10_STCA100 8815

#define EPTPC_CFG_W10_TIME 32

#endif
