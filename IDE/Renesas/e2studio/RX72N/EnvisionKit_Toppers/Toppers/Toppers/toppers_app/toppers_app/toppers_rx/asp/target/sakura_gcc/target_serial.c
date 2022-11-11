/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 by Naoki Saito
 *             Nagoya Municipal Industrial Research Institute, JAPAN
 *  Copyright (C) 2003-2004 by Platform Development Center
 *                                          RICOH COMPANY,LTD. JAPAN
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
 *	RX610 UART用シリアルI/Oモジュール
 */
#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "target_board.h"
#include "target_serial.h"
#include "target_syssvc.h"

dnode_id pid_to_devid_table[TNUM_PORT] = {
  DEV_SCIC0
};
#define PID_TO_DEV(siopid) (pid_to_devid_table[siopid-1])

/*
 *  カーネル起動時のバナー出力用の初期化
 */
void
std_uart_init(ID siopid, uint8_t bitrate, uint8_t clksrc)
{
	SIOPCB  *p_siopcb ;
	dnode_id sci_did;
	const SIOPINIB *p_siopinib;

	sci_did = PID_TO_DEV(siopid);
	p_siopcb = (SIOPCB*)GET_DEV_STAT(sci_did);
	p_siopinib = p_siopcb->p_siopinib;

	/*  二重初期化の防止  */
	p_siopcb->is_initialized = true;

	/*  ハードウェアの初期化処理と送信許可  */
	scic_uart_setmode(p_siopinib , bitrate, clksrc);
	scic_uart_trans_enable(p_siopcb);
}
/*
 *  シリアルI/Oポートへのポーリングでの出力
 */
void
sci_uart_pol_putc(char c, ID siopid)
{
	SIOPCB  *p_siopcb ;
	dnode_id sci_did;
	const SIOPINIB *p_siopinib;

	sci_did = PID_TO_DEV(siopid);
	p_siopcb = (SIOPCB*)GET_DEV_STAT(sci_did);
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  送信レジスタが空になるまで待つ
	 */

	// wata while((sil_reb_mem(
		//	(void *)p_siopinib->ssrreg) & SCI_SSR_TEND_BIT) == 0U);

	sil_wrb_mem((void *)p_siopinib->tdreg, (uint8_t)c);
}


/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB  *p_siopcb = NULL;
	ER      ercd;
	
	/*
	 *  シリアルI/O割込みをマスクする．
	 *  (dis_int関数は、"\kernel\interrupt.c"に記述)
	 */
//wata	ercd = dis_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
//wata 	ercd = dis_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
	
	p_siopcb = (SIOPCB*)GET_DEV_STAT(PID_TO_DEV(siopid));
    scic_uart_opn_por(p_siopcb , exinf , UART_BAUDRATE , UART_CLKSRC);

	/*
	 *  シリアルI/O割込みをマスク解除する．
	 *  (ena_int関数は、"\kernel\interrupt.c"に記述)
	 */
//wata	ercd = ena_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
//wata	ercd = ena_int(INTNO_SIO_RX);
	assert(ercd == E_OK);

	return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	ER        ercd;

	/*
	 *  デバイス依存のクローズ処理．
	 */
	scic_uart_cls_por(p_siopcb);
	
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
//wata	ercd = dis_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
//wata	ercd = dis_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
}

/*
 *  SIOの割込みハンドラ
 */
void sio_tx_isr(intptr_t exinf)
{
  scic_uart_tx_isr(PID_TO_DEV(exinf));
}

/*
 *  SIOの割込みハンドラ
 */
void sio_rx_isr(intptr_t exinf)
{
  scic_uart_rx_isr(PID_TO_DEV(exinf));
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t
sio_snd_chr(SIOPCB *siopcb, char c)
{
	return(scic_uart_snd_chr(siopcb, c));
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
	return(scic_uart_rcv_chr(siopcb));
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	scic_uart_ena_cbr(siopcb, cbrtn);
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
	scic_uart_dis_cbr(siopcb, cbrtn);
}

/*
 *  シリアルI/Oポートからの送信可能コールバック
 */
void
scic_uart_irdy_snd(intptr_t exinf)
{
	/* 共通部（syssvc\serial.c）にあるsio_irdy_snd関数を呼び出し*/
	sio_irdy_snd(exinf);
}

/*
 *  シリアルI/Oポートからの受信通知コールバック
 */
void
scic_uart_irdy_rcv(intptr_t exinf)
{
	/* 共通部（syssvc\serial.c）にあるsio_irdy_rcv関数を呼び出し*/
	sio_irdy_rcv(exinf);
}

