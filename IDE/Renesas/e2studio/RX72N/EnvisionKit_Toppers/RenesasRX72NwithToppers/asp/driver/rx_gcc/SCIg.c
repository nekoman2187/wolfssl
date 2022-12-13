/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008-2010 by Witz Corporation, JAPAN
 *  Copyright (C) 2016 by Hisashi Hata, JAPAN
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
 *   Renesas SCIc(UART)用 簡易SIOドライバ
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "SCIg.h"

#define SCI_SCR_FLG_ENABLE	(SCIG_SCR_RE | SCIG_SCR_TE)
#define SCI_SMR_FLG_ENABLE	(SCIG_SMR_STOP | SCIG_SMR_PM | SCIG_SMR_PE | SCIG_SMR_CHR | SCIG_SMR_CM)

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */

#define get_siopinib(siopcb_stat) (siopcb_stat->p_siopinib)

/*
 * enable transmit
 */
void
scic_uart_trans_enable(void* p_siopcb_v){
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;

	p_siopcb = (SIOPCB*) p_siopcb_v;
	p_siopinib = p_siopcb->p_siopinib;
	sil_wrb_mem((void *)p_siopinib->ctlreg,
					(uint8_t)(sil_reb_mem((void *)p_siopinib->ctlreg) | SCIG_SCR_TE));
}
/*
 *  SIOドライバのシリアルモードレジスタ(SMR)
 */
void
scic_uart_setmode(const SIOPINIB *p_siopinib, uint8_t bitrate, uint8_t clksrc)
{
	uint8_t i;

	/*
	 *  SCIドライバの初期化ルーチン
	 */

	/*
	 *  割り込み要求先レジスタの設定(ISELRi)
	 *
	 *  リセット値と同じ値を設定することになるため,
	 *  処理は省略する.
	 */

	/* 送受信禁止, SCKn端子は入出力ポートとして使用 */
	sil_wrb_mem((void *)p_siopinib->ctlreg, 0x00U);

	/* クロック選択ビット(SMR.CKS[1:0]ビットを設定) */
	sil_wrb_mem((void *)p_siopinib->modereg, 
					 clksrc);
	/* ビットレートを設定 */
	sil_wrb_mem((void *)p_siopinib->bitratereg, bitrate);

	/* ビット期間(基本クロック16サイクルの期間が1ビット期間となる) */
	while(i < 16){
		i++;
	}

	/* 送受信許可 */
	sil_wrb_mem((void *)p_siopinib->ctlreg, 
			(sil_reb_mem((void *)p_siopinib->ctlreg) | SCI_SCR_FLG_ENABLE));
}

/*
 *  シリアルI/Oポートのオープン
 */
void
scic_uart_opn_por
	(void* p_siopcb_v, intptr_t exinf, uint8_t bitrate, uint8_t clksrc)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;

	p_siopcb = (SIOPCB*) p_siopcb_v;
	p_siopinib = p_siopcb->p_siopinib;

	/*
	 *  ハードウェアの初期化
	 *
	 *  既に初期化している場合は, 二重に初期化しない.
	 */
	if(!(p_siopcb->is_initialized)){
		scic_uart_setmode(p_siopinib, bitrate, clksrc);
		p_siopcb->is_initialized = true;
	}

	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;

}

/*
 *  シリアルI/Oポートのクローズ
 */
void
scic_uart_cls_por(void *p_siopcb_v)
{
	/*
	 *  UART停止
	 */
  SIOPCB *p_siopcb;
  p_siopcb = p_siopcb_v;
  sil_wrh_mem((void *)p_siopcb->p_siopinib->ctlreg, 0x00U);
  p_siopcb->openflag = false;
  p_siopcb->is_initialized = false;
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t
scic_uart_snd_chr(void *p_siopcb_v, char c)
{
	bool_t ercd = false;
    SIOPCB *p_siopcb;

    p_siopcb = (SIOPCB *)p_siopcb_v;
	if((sil_reb_mem((void *)p_siopcb->p_siopinib->ssrreg) & SCIG_SSR_TEND) != 0){
		sil_wrb_mem((void *)p_siopcb->p_siopinib->tdreg, (uint8_t)c);
		ercd = true;
	}

	return ercd;
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
scic_uart_rcv_chr(void *p_siopcb_v)
{
	int_t c = -1;
    SIOPCB *p_siopcb;

    p_siopcb = (SIOPCB *)p_siopcb_v;

	/*
	 *  受信フラグがONのときのみ受信バッファから文字を取得する.
	 *  これは, ポーリング受信に対応するためである.
	 *  しかし, SCICでは受信フラグがないこと, システムサービス
	 *  では受信割込みの中からしかデータを受信しに来ないことから, 常に
	 *  受信バッファから文字を取得する.
	 */
	c = (int)(sil_reb_mem((void *)p_siopcb->p_siopinib->rdreg));

	return c;
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
scic_uart_ena_cbr(void *p_siopcb_v, uint_t cbrtn)
{
    SIOPCB *p_siopcb;

    p_siopcb = (SIOPCB *)p_siopcb_v;
	switch (cbrtn) {
		case SIO_RDY_SND:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) | SCIG_SCR_TIE));
			break;
		case SIO_RDY_RCV:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) | SCIG_SCR_RIE));
			break;
		default:
			assert(1);
			break;
	}
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
scic_uart_dis_cbr(void *p_siopcb_v, uint_t cbrtn)
{
    SIOPCB *p_siopcb;

    p_siopcb = (SIOPCB *)p_siopcb_v;
	switch (cbrtn) {
		case SIO_RDY_SND:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) & (~SCIG_SCR_TIE)));
			break;
		case SIO_RDY_RCV:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) & (~SCIG_SCR_RIE)));
			break;
		default:
			assert(1);
			break;
	}
}

/*
 *  SIOの割込みサービスルーチン
 */
void
scic_uart_tx_isr(dnode_id sio_did)
{
  SIOPCB *p_siopcb = GET_DEV_STAT(sio_did);

  if((sil_reb_mem(
       (void *)p_siopcb->p_siopinib->ssrreg) & SCIG_SSR_TEND) != 0U){
    /*
     *  送信可能コールバックルーチンを呼び出す．
     */
    scic_uart_irdy_snd(p_siopcb->exinf);
  }
}

void
scic_uart_rx_isr(dnode_id sio_did)
{
  SIOPCB	*p_siopcb = (SIOPCB*)GET_DEV_STAT(sio_did);

  /*
   *  受信フラグがONのときのみ受信通知コールバックルーチンを呼び出す.
   *  しかし, SCICでは受信フラグがないため, 常に受信通知
   *  コールバックルーチンを呼び出す.
   *  ここでは受信割込みの発生を信じる.
   */
  /*
   *  受信通知コールバックルーチンを呼び出す．
   */
  scic_uart_irdy_rcv(p_siopcb->exinf);
}

