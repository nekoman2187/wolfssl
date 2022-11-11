/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2010 by Witz Corporation, JAPAN
 *  Copyright (C) 2015- by Hisashi Hata, JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

#include <kernel_impl.h>

/*
 *		プロセッサ依存モジュール（RX63n用）
 */

#define NULL_OFF 0 //reserved IPR 

volatile uint8_t const ipr_reg_offset[ INHNO_MAX ] = {
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,	/* No.0 - 4   予約 */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,	/* No.5 - 9   予約 */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,	/* No.10 - 14 予約 */
	NULL_OFF,							/* No.15  予約 */
	ICU_IPR00_OFFSET,					/* No.16   バスエラー BUSERR  */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,			/* No.17 - 20 予約 */
	ICU_IPR01_OFFSET,					/* No.21   FCU FIFERR  */
	NULL_OFF,							/* No.22  予約 */
	ICU_IPR02_OFFSET,					/* No.23   FCU FRDYI  */
	NULL_OFF, NULL_OFF, NULL_OFF,		        /* No.24 -26  予約 */
	ICU_IPR03_OFFSET,                 /* No.27  ICU SWINT  */
	ICU_IPR04_OFFSET,					/* No.28   CMTユニット0 CMT0  */
	ICU_IPR05_OFFSET,					/* No.29   CMTユニット0 CMT1  */
	ICU_IPR06_OFFSET,					/* No.30   CMTユニット1 CMT2  */
	ICU_IPR07_OFFSET,					/* No.31   CMTユニット1 CMT3  */
	ICU_IPR20_OFFSET,                 /* No.32   Ether EINT  */
	ICU_IPR21_OFFSET,                 /* No.33   USB D0FIFO0  */
	ICU_IPR22_OFFSET,                 /* No.34   USB D1FIFO0  */
	ICU_IPR23_OFFSET,                 /* No.35   USB USBI0  */
	ICU_IPR24_OFFSET,                 /* No.36   USB D0FIFO1  */
	ICU_IPR25_OFFSET,                 /* No.37   USB D1FIFO1  */
	ICU_IPR26_OFFSET,                 /* No.38   USB USBI1  */
	ICU_IPR27_OFFSET,                 /* No.39   RSPI0 SPRI0  */
	ICU_IPR27_OFFSET,                 /* No.40   RSPI0 SPTI0  */
	ICU_IPR27_OFFSET,                 /* No.41   RSPI0 SPII0  */
	ICU_IPR2A_OFFSET,                 /* No.42   RSPI1 SPRI0  */
	ICU_IPR2A_OFFSET,                 /* No.43   RSPI1 SPTI0  */
	ICU_IPR2A_OFFSET,                 /* No.44   RSPI1 SPII0  */
	ICU_IPR2D_OFFSET,                 /* No.45   RSPI1 SPRI0  */
	ICU_IPR2D_OFFSET,                 /* No.46   RSPI1 SPTI0  */
	ICU_IPR2D_OFFSET,                 /* No.47   RSPI1 SPII0  */
	ICU_IPR30_OFFSET,                 /* NO.48  CAN0 RXF0*/
	ICU_IPR30_OFFSET,                 /* NO.49  CAN0 TXF0*/
	ICU_IPR30_OFFSET,                 /* NO.50  CAN0 RXM0*/
	ICU_IPR30_OFFSET,                 /* NO.51  CAN0 TXM0*/
	ICU_IPR34_OFFSET,                 /* NO.52  CAN1 RXF1*/
	ICU_IPR34_OFFSET,                 /* NO.53  CAN1 TXF1*/
	ICU_IPR34_OFFSET,                 /* NO.54  CAN1 RXM1*/
	ICU_IPR34_OFFSET,                 /* NO.55  CAN1 TXM1*/
	ICU_IPR38_OFFSET,                 /* NO.56  CAN2 RXF2*/
	ICU_IPR38_OFFSET,                 /* NO.57  CAN2 TXF2*/
	ICU_IPR38_OFFSET,                 /* NO.58  CAN2 RXM2*/
	ICU_IPR38_OFFSET,                 /* NO.59  CAN2 TXM2*/
	NULL_OFF, NULL_OFF,                     /* No.60 - 61 予約 */
	ICU_IPR3E_OFFSET,                 /* NO 62 RTC CUP */
	NULL_OFF,						    /* No.63 予約 */
	ICU_IPR40_OFFSET,					/* No.64   外部端子 IRQ0  */
	ICU_IPR41_OFFSET,					/* No.65   外部端子 IRQ1  */
	ICU_IPR42_OFFSET,					/* No.66   外部端子 IRQ2  */
	ICU_IPR43_OFFSET,					/* No.67   外部端子 IRQ3  */
	ICU_IPR44_OFFSET,					/* No.68   外部端子 IRQ4  */
	ICU_IPR45_OFFSET,					/* No.69   外部端子 IRQ5  */
	ICU_IPR46_OFFSET,					/* No.70   外部端子 IRQ6  */
	ICU_IPR47_OFFSET,					/* No.71   外部端子 IRQ7  */
	ICU_IPR48_OFFSET,					/* No.72   外部端子 IRQ8  */
	ICU_IPR49_OFFSET,					/* No.73   外部端子 IRQ9  */
	ICU_IPR4A_OFFSET,					/* No.74   外部端子 IRQ10  */
	ICU_IPR4B_OFFSET,					/* No.75   外部端子 IRQ11  */
	ICU_IPR4C_OFFSET,					/* No.76   外部端子 IRQ12  */
	ICU_IPR4D_OFFSET,					/* No.77   外部端子 IRQ13  */
	ICU_IPR4E_OFFSET,					/* No.78   外部端子 IRQ14  */
	ICU_IPR4F_OFFSET,					/* No.79   外部端子 IRQ15  */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,	/* No.80 - 84 予約 */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,	/* No.85 - 89 予約 */
    ICU_IPR5A_OFFSET,                 /* No.90  USB USBR0  */
	ICU_IPR5B_OFFSET,                 /* No.91  USB USBR1  */
	ICU_IPR5C_OFFSET,                 /* No.92  RTC ALM  */
	ICU_IPR5D_OFFSET,                 /* No.93  RTC PRD  */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,         /* No.94 - 97  予約 */
	ICU_IPR62_OFFSET,					/* No.98   AD0 ADI0  */
    NULL_OFF, NULL_OFF, NULL_OFF,               /* No.99 - 101 予約 */
	ICU_IPR66_OFFSET,					/* No.102  S12AD S12ADI0  */
	NULL_OFF, NULL_OFF, NULL_OFF,               /* No.103 - 105 予約 */
	ICU_IPR6A_OFFSET,					/* No.106  ICU GROUP0  */
	ICU_IPR6B_OFFSET,					/* No.107  ICU GROUP1  */
	ICU_IPR6C_OFFSET,					/* No.108  ICU GROUP2  */
	ICU_IPR6D_OFFSET,					/* No.109  ICU GROUP3  */
	ICU_IPR6E_OFFSET,					/* No.110  ICU GROUP4  */
	ICU_IPR6F_OFFSET,					/* No.111  ICU GROUP5  */
	ICU_IPR70_OFFSET,					/* No.112  ICU GROUP6  */
	ICU_IPR71_OFFSET,                           /* No.113 予約 */
	ICU_IPR72_OFFSET,                 /* No.114  ICU Group12  */
	NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF, NULL_OFF,   /* No.115 - 119 予約 */
	NULL_OFF, NULL_OFF,                     /* No.120 - 121 予約 */
	ICU_IPR7A_OFFSET,                 /* No.122  SCI12 SCIX0  */
	ICU_IPR7A_OFFSET,                 /* No.123  SCI12 SCIX1  */
	ICU_IPR7A_OFFSET,                 /* No.124  SCI12 SCIX2  */
	ICU_IPR7A_OFFSET,                 /* No.125  SCI12 SCIX3  */
	ICU_IPR7E_OFFSET,                 /* No.126  TPU0 TGI0A  */
	ICU_IPR7E_OFFSET,                 /* No.127  TPU0 TGI0B  */
	ICU_IPR7E_OFFSET,                 /* No.128  TPU0 TGI0C  */
	ICU_IPR7E_OFFSET,                 /* No.129  TPU0 TGI0D  */
	ICU_IPR82_OFFSET,                 /* No.130  TPU1 TGI1A  */
	ICU_IPR82_OFFSET,                 /* No.131  TPU1 TGI1B  */
    ICU_IPR84_OFFSET,                 /* No.132  TPU2 TGI2A  */
    ICU_IPR84_OFFSET,                 /* No.133  TPU2 TGI2B  */
    ICU_IPR86_OFFSET,                 /* No.134  TPU3 TGI3A  */
    ICU_IPR86_OFFSET,                 /* No.135  TPU3 TGI3B  */
    ICU_IPR86_OFFSET,                 /* No.136  TPU3 TGI3C  */
    ICU_IPR86_OFFSET,                 /* No.137  TPU3 TGI3D  */
    ICU_IPR8A_OFFSET,                 /* No.138  TPU4 TGI4A  */
    ICU_IPR8A_OFFSET,                 /* No.139  TPU4 TGI4B  */
    ICU_IPR8C_OFFSET,                 /* No.140  TPU5 TGI5A  */
    ICU_IPR8C_OFFSET,                 /* No.141  TPU5 TGI5B  */
    ICU_IPR8E_OFFSET,                 /* No.142  TPU6 TGI6A, MTU0 TGIA0  */
    ICU_IPR8E_OFFSET,                 /* No.143  TPU6 TGI6B, MTU0 TGIB0  */
    ICU_IPR8E_OFFSET,                 /* No.144  TPU6 TGI6C, MTU0 TGIC0  */
    ICU_IPR8E_OFFSET,                 /* No.145  TPU6 TGI6D, MTU0 TGID0  */
    ICU_IPR92_OFFSET,                 /* No.146  MTU0 TGIE0  */
    ICU_IPR92_OFFSET,                 /* No.147  MTU0 TGIF0  */
    ICU_IPR94_OFFSET,                 /* No.148  TPU7 TGI7A, MTU1 TGIA1  */
    ICU_IPR94_OFFSET,                 /* No.149  TPU7 TGI7B, MTU1 TGIB1  */
    ICU_IPR96_OFFSET,                 /* No.150  TPU8 TGI8A, MTU2 TGIA2  */
    ICU_IPR96_OFFSET,                 /* No.151  TPU8 TGI8B, MTU2 TGIB2  */
    ICU_IPR98_OFFSET,                 /* No.152  TPU9 TGI9A, MTU3 TGIA3  */
    ICU_IPR98_OFFSET,                 /* No.153  TPU9 TGI9B, MTU3 TGIB3  */
    ICU_IPR98_OFFSET,                 /* No.154  TPU9 TGI9C, MTU3 TGIC3  */
    ICU_IPR98_OFFSET,                 /* No.155  TPU9 TGI9D, MTU3 TGID3  */
    ICU_IPR9C_OFFSET,                 /* No.156  TPU10 TGI10A, MTU4 TGIA4  */
    ICU_IPR9C_OFFSET,                 /* No.157  TPU10 TGI10B, MTU4 TGIB4  */
    ICU_IPR9C_OFFSET,                 /* No.158  MTU4 TGIC4  */
    ICU_IPR9C_OFFSET,                 /* No.159  MTU4 TGID4  */
    ICU_IPRA0_OFFSET,                 /* No.160  MTU4 TGIV4  */
    ICU_IPRA1_OFFSET,                 /* No.161  MTU5 TGIU5  */
    ICU_IPRA1_OFFSET,                 /* No.162  MTU5 TGIV5  */
    ICU_IPRA1_OFFSET,                 /* No.163  MTU5 TGIW5  */
    ICU_IPRA4_OFFSET,                 /* No.164  TPU11 TGI11A  */
    ICU_IPRA4_OFFSET,                 /* No.165  TPU11 TGI11B  */
    ICU_IPRA6_OFFSET,                 /* No.166  POE OEI1  */
    ICU_IPRA6_OFFSET,                 /* No.167  POE OEI2  */
	NULL_OFF, NULL_OFF,                     /* No.168 - 169 予約 */
    ICU_IPRAA_OFFSET,                 /* No.170  TMR0 CMIA0  */
    ICU_IPRAA_OFFSET,                 /* No.171  TMR0 CMIB0  */
    ICU_IPRAA_OFFSET,                 /* No.172  TMR0 OVI0  */
    ICU_IPRAD_OFFSET,                 /* No.173  TMR1 CMIA1  */
    ICU_IPRAD_OFFSET,                 /* No.174  TMR1 CMIB1  */
    ICU_IPRAD_OFFSET,                 /* No.175  TMR1 OVI1  */
    ICU_IPRB0_OFFSET,                 /* No.176  TMR2 CMIA2  */
    ICU_IPRB0_OFFSET,                 /* No.177  TMR2 CMIB2  */
    ICU_IPRB0_OFFSET,                 /* No.178  TMR2 OVI2  */
    ICU_IPRB3_OFFSET,                 /* No.179  TMR3 CMIA3  */
    ICU_IPRB3_OFFSET,                 /* No.180  TMR3 CMIB3  */
    ICU_IPRB3_OFFSET,                 /* No.181  TMR3 OVI3  */
    ICU_IPRB6_OFFSET,                 /* No.182  RIIC0 EEI0  */
    ICU_IPRB7_OFFSET,                 /* No.183  RIIC0 RXI0  */
    ICU_IPRB8_OFFSET,                 /* No.184  RIIC0 TXI0  */
    ICU_IPRB9_OFFSET,                 /* No.185  RIIC0 TEI0  */
    ICU_IPRBA_OFFSET,                 /* No.186  RIIC1 EEI1  */
    ICU_IPRBB_OFFSET,                 /* No.187  RIIC1 RXI1  */
    ICU_IPRBC_OFFSET,                 /* No.188  RIIC1 TXI1  */
    ICU_IPRBD_OFFSET,                 /* No.189  RIIC1 TEI1  */
    ICU_IPRBE_OFFSET,                 /* No.190  RIIC2 EEI2  */
    ICU_IPRBF_OFFSET,                 /* No.191  RIIC2 RXI2  */
    ICU_IPRC0_OFFSET,                 /* No.192  RIIC2 TXI2  */
    ICU_IPRC1_OFFSET,                 /* No.193  RIIC2 TEI2  */
    ICU_IPRC2_OFFSET,                 /* No.194  RIIC3 EEI3  */
    ICU_IPRC3_OFFSET,                 /* No.195  RIIC3 RXI3  */
    ICU_IPRC4_OFFSET,                 /* No.196  RIIC3 TXI3  */
    ICU_IPRC5_OFFSET,                 /* No.197  RIIC3 TEI3  */
    ICU_IPRC6_OFFSET,                 /* No.198  DMAC DMAC0I  */
    ICU_IPRC7_OFFSET,                 /* No.199  DMAC DMAC1I  */
    ICU_IPRC8_OFFSET,                 /* No.200  DMAC DMAC2I  */
    ICU_IPRC9_OFFSET,                 /* No.201  DMAC DMAC3I  */
    ICU_IPRCA_OFFSET,                 /* No.202  EXDMAC EXDMAC0I  */
    ICU_IPRCB_OFFSET,                 /* No.203  EXDMAC EXDMAC1I  */
	NULL_OFF, NULL_OFF,                     /* No.204 - 205 予約 */
    ICU_IPRCE_OFFSET,                 /* No.206  DEU DEU0  */
    ICU_IPRCF_OFFSET,                 /* No.207  DEU DEU0  */
    ICU_IPRD0_OFFSET,                 /* No.208  PDC PCDFI  */
    ICU_IPRD1_OFFSET,                 /* No.209  PDC PCFEI  */
    ICU_IPRD2_OFFSET,                 /* No.210  PDC PCERI  */
	NULL_OFF, NULL_OFF, NULL_OFF,               /* No.211 - 213 予約 */
    ICU_IPRD6_OFFSET,                 /* No.214  SCI0 RXI0  */
    ICU_IPRD6_OFFSET,                 /* No.215  SCI0 TXI0  */
    ICU_IPRD6_OFFSET,                 /* No.216  SCI0 TEI0  */
    ICU_IPRD9_OFFSET,                 /* No.217  SCI1 RXI1  */
    ICU_IPRD9_OFFSET,                 /* No.218  SCI1 TXI1  */
    ICU_IPRD9_OFFSET,                 /* No.219  SCI1 TEI1  */
    ICU_IPRDC_OFFSET,                 /* No.220  SCI2 RXI2  */
    ICU_IPRDC_OFFSET,                 /* No.221  SCI2 TXI2  */
    ICU_IPRDC_OFFSET,                 /* No.222  SCI2 TEI2  */
    ICU_IPRDF_OFFSET,                 /* No.223  SCI3 RXI3  */
    ICU_IPRDF_OFFSET,                 /* No.224  SCI3 TXI3  */
    ICU_IPRDF_OFFSET,                 /* No.225  SCI3 TEI3  */
    ICU_IPRE2_OFFSET,                 /* No.226  SCI4 RXI4  */
    ICU_IPRE2_OFFSET,                 /* No.227  SCI4 TXI4  */
    ICU_IPRE2_OFFSET,                 /* No.228  SCI4 TEI4  */
    ICU_IPRE5_OFFSET,                 /* No.229  SCI5 RXI5  */
    ICU_IPRE5_OFFSET,                 /* No.230  SCI5 TXI5  */
    ICU_IPRE5_OFFSET,                 /* No.231  SCI5 TEI5  */
    ICU_IPRE8_OFFSET,                 /* No.232  SCI6 RXI6  */
    ICU_IPRE8_OFFSET,                 /* No.233  SCI6 TXI6  */
    ICU_IPRE8_OFFSET,                 /* No.234  SCI6 TEI6  */
    ICU_IPREB_OFFSET,                 /* No.235  SCI7 RXI7  */
    ICU_IPREB_OFFSET,                 /* No.236  SCI7 TXI7  */
    ICU_IPREB_OFFSET,                 /* No.237  SCI7 TEI7  */
    ICU_IPREE_OFFSET,                 /* No.238  SCI8 RXI8  */
    ICU_IPREE_OFFSET,                 /* No.239  SCI8 TXI8  */
    ICU_IPREE_OFFSET,                 /* No.240  SCI8 TEI8  */
    ICU_IPRF1_OFFSET,                 /* No.241  SCI9 RXI9  */
    ICU_IPRF1_OFFSET,                 /* No.242  SCI9 TXI9  */
    ICU_IPRF1_OFFSET,                 /* No.243  SCI9 TEI9  */
    ICU_IPRF4_OFFSET,                 /* No.244  SCI10 RXI10  */
    ICU_IPRF4_OFFSET,                 /* No.245  SCI10 TXI10  */
    ICU_IPRF4_OFFSET,                 /* No.246  SCI10 TEI10  */
    ICU_IPRF7_OFFSET,                 /* No.247  SCI11 RXI11  */
    ICU_IPRF7_OFFSET,                 /* No.248  SCI11 TXI11  */
    ICU_IPRF7_OFFSET,                 /* No.249  SCI11 TEI11  */
    ICU_IPRFA_OFFSET,                 /* No.250  SCI12 RXI12  */
    ICU_IPRFA_OFFSET,                 /* No.251  SCI12 TXI12  */
    ICU_IPRFA_OFFSET,                 /* No.252  SCI12 TEI12  */
    ICU_IPRFD_OFFSET,                 /* No.253  IEB IEBINT  */
	NULL_OFF, NULL_OFF,						/* No.254 - 255 予約 */
};

/*
 * set interrupt priority register
 */

void set_icu_ipr(INTNO intno, uint8_t pri_num){
  *((volatile uint8_t *)(ICU_IPR_BASE + ipr_reg_offset[intno])) = pri_num;
}
