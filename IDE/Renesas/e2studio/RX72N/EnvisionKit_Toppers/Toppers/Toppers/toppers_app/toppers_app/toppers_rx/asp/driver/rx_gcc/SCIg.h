/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
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

/*
 *  RX64M UART用 簡易SIOドライバ
 */

#ifndef TOPPERS_RX_SCIG_H
#define TOPPERS_RX_SCIG_H

#include <sil.h>
#include <target_device/target_device.h>

/* Register offset */
#define SCIG_SMR_OFFSET 0x0
#define SCIG_BRR_OFFSET 0x1
#define SCIG_SCR_OFFSET 0x2
#define SCIG_TDR_OFFSET 0x3
#define SCIG_SSR_OFFSET 0x4
#define SCIG_RDR_OFFSET 0x5
#define SCIG_SCMR_OFFSET 0x6
#define SCIG_SEMR_OFFSET 0x7
#define SCIG_SNFR_OFFSET 0x8
#define SCIG_SIMR1_OFFSET 0x9
#define SCIG_SIMR2_OFFSET 0xA
#define SCIG_SIMR3_OFFSET 0xB
#define SCIG_SISR_OFFSET 0xC
#define SCIG_SPMR_OFFSET 0xD
#define SCIG_TDRH_OFFSET 0xE
#define SCIG_TDRL_OFFSET 0xF
#define SCIG_TDRHL_OFFSET 0xE
#define SCIG_RDRH_OFFSET 0x10
#define SCIG_RDRL_OFFSET 0x11
#define SCIG_RDRHL_OFFSET 0x10
#define SCIG_MDDR_OFFSET 0x12

/* シリアルモードレジスタ（SMR) */
#define SCIG_SMR_CKS			UINT_C(0x03)
#define SCIG_SMR_STOP		UINT_C(0x08)
#define SCIG_SMR_PM			UINT_C(0x10)
#define SCIG_SMR_PE			UINT_C(0x20)
#define SCIG_SMR_CHR			UINT_C(0x40)
#define SCIG_SMR_CM			UINT_C(0x80)
#define SCIG_SMR_ASYNC_7BIT	UINT_C(0x00)
#define SCIG_SMR_ASYNC_8BIT	UINT_C(0x40)

/* シリアルコントロールレジスタ（SCR) */
#define SCIG_SCR_CKE			UINT_C(0x03)
#define SCIG_SCR_TEIE		UINT_C(0x04)
#define SCIG_SCR_RE			UINT_C(0x10)
#define SCIG_SCR_TE			UINT_C(0x20)
#define SCIG_SCR_RIE			UINT_C(0x40)
#define SCIG_SCR_TIE			UINT_C(0x80)

/* シリアルステータスレジスタ（SSR） */
#define SCIG_SSR_TEND UINT_C(0x04)
#define SCIG_SSR_PER UINT_C(0x08)
#define SCIG_SSR_FER UINT_C(0x10)
#define SCIG_SSR_ORER UINT_C(0x20)

#define SCIG_SCMR_SMIF UINT_C(0x1)
#define SCIG_SCMR_SINV UINT_C(0x4)
#define SCIG_SCMR_SDIR UINT_C(0x8)
#define SCIG_SCMR_CHR1 UINT_C(0x10)
#define SCIG_SCMR_BCP2 UINT_C(0x80)
#define SCIG_SCMR_RESERVE UINT_C(0x62)

/* シリアル拡張モードレジスタ（SEMR) */
#define SCIG_SEMR_ACS0		UINT_C(0x01)
#define SCIG_SEMR_ABCS		UINT_C(0x10)

/* 指定可能なクロックソース */
#define CLK_F1	UINT_C(0x00)
#define CLK_F4	UINT_C(0x01)
#define CLK_F16	UINT_C(0x02)
#define CLK_F64	UINT_C(0x03)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	volatile uint8_t	*ctlreg;		/* シリアルコントロールレジスタ（SCR) */
	volatile uint8_t	*modereg;		/* シリアルモードレジスタ（SMR) */
	volatile uint8_t	*extmodereg;	/* シリアル拡張モードレジスタ（SEMR) */	
	volatile uint8_t	*statusreg;		/* シリアルステータスレジスタ（SSR） */
	volatile uint8_t	*tdreg;			/* トランスミットデータレジスタ（TDR)*/
	volatile uint8_t	*rdreg;			/* レシーブデータレジスタ（RDR) */
	volatile uint8_t	*bitratereg;	/* ビットレートレジスタ（BRR) */
	volatile uint8_t	*ssrreg;		/* ステータスレジスタ */
	uint8_t				tx_intno;		/* 送信（データエンプティ）割り込み番号 */
	uint8_t				rx_intno;		/* 受信（データフル）割り込み番号 */
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB	*p_siopinib; 				/* シリアルI/Oポート初期化ブロック */
	intptr_t 	exinf;			 				/* 拡張情報 */
	bool_t		openflag;						/* オープン済みフラグ */
	bool_t		sendflag;						/* 送信割込みイネーブルフラグ */
	bool_t		getready;						/* 文字を受信した状態 */
	bool_t		putready;						/* 文字を送信できる状態 */
	bool_t		is_initialized; 				/* デバイス初期化済みフラグ */
};

typedef struct sio_port_control_block	SIOPCB;

/*
 *  コールバックルーチンの識別番号
 */
#define SIO_RDY_SND    (1U)        /* 送信可能コールバック */
#define SIO_RDY_RCV    (2U)        /* 受信通知コールバック */

/*
 *  シリアルI/Oポートのオープン
 */
extern void scic_uart_opn_por
	(void* p_siopcb_v, intptr_t exinf , uint8_t baud , uint8_t clksrc);

/*
 *  シリアルI/Oポートのクローズ
 */
extern void scic_uart_cls_por(void *p_siopcb);

/*
 *  シリアルI/Oポートへの文字送信
 */
extern bool_t scic_uart_snd_chr(void *p_siopcb, char c);

/*
 *  シリアルI/Oポートからの文字受信
 */
extern int_t scic_uart_rcv_chr(void *p_siopcb);

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
extern void  scic_uart_ena_cbr(void *p_siopcb, uint_t cbrtn);

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
extern void scic_uart_dis_cbr(void *p_siopcb, uint_t cbrtn);

/*
 *  SIOの割込みサービスルーチン
 */
extern void scic_uart_tx_isr(dnode_id sio_did);
extern void scic_uart_rx_isr(dnode_id sio_did);

/*
 *  シリアルI/Oポートからの送信可能コールバック
 */
extern void scic_uart_irdy_snd(intptr_t exinf);

/*
 *  シリアルI/Oポートからの受信通知コールバック
 */
extern void scic_uart_irdy_rcv(intptr_t exinf);

/*
 * enable transmit
 */
void
scic_uart_trans_enable(void* p_siopcb_v);

void
scic_uart_setmode(const SIOPINIB *p_siopinib, uint8_t bitrate, uint8_t clksrc);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_RX_SCIG_H */
