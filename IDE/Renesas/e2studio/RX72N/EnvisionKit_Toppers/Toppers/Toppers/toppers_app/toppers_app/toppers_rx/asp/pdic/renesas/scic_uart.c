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
 *   Renesas SCIc(UART)用 簡易SIOドライバ
 */

#include <sil.h>
#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "scic_uart.h"

/* シリアルモードレジスタ（SMR) */
#define CKS			UINT_C(0x03)
#define STOP		UINT_C(0x08)
#define PM			UINT_C(0x10)
#define PE			UINT_C(0x20)
#define CHR			UINT_C(0x40)
#define CM			UINT_C(0x80)
#define ASYNC_7BIT	UINT_C(0x00)
#define ASYNC_8BIT	UINT_C(0x40)

/* シリアルコントロールレジスタ（SCR) */
#define CKE			UINT_C(0x03)
#define TEIE		UINT_C(0x04)
#define RE			UINT_C(0x10)
#define TE			UINT_C(0x20)
#define RIE			UINT_C(0x40)
#define TIE			UINT_C(0x80)

/* シリアルステータスレジスタ（SSR） */
#define TEND		UINT_C(0x04)
#define PER			UINT_C(0x08)
#define FER			UINT_C(0x10)
#define ORER		UINT_C(0x20)

/* シリアル拡張モードレジスタ（SEMR) */
#define ACS0		UINT_C(0x01)
#define ABCS		UINT_C(0x10)

#define SCI_SCR_FLG_ENABLE	(RE | TE)
#define SCI_SMR_FLG_ENABLE	(STOP | PM | PE | CHR | CM)

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
	volatile uint32_t	*mstpcrreg;		/* モジュールストップコントロールレジスタ（MSTPCR） */
	volatile uint8_t	*ssrreg;		/* ステータスレジスタ */
	uint8_t				tx_intno;		/* 送信（データエンプティ）割り込み番号 */
	uint8_t				rx_intno;		/* 受信（データフル）割り込み番号 */
	uint8_t				te_intno;		/* 送信（終了）割り込み番号 */
	uint8_t				sci_no;			/* SCIの番号(SCI0〜SCI6) */
	uint32_t			mstpcr_offset;	/* MSTPCRの対応するビットオフセット */
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

/*
 *  シリアルI/Oポート管理ブロックのエリア
 */
static SIOPCB	siopcb_table[TNUM_SIOP];

/* レジスタテーブル */
static const SIOPINIB siopinib_table[TNUM_SIOP] =
{
	{
		(volatile uint8_t *)SCI0_SCR_ADDR,
		(volatile uint8_t *)SCI0_SMR_ADDR,
		(volatile uint8_t *)SCI0_SEMR_ADDR,
		(volatile uint8_t *)SCI0_SSR_ADDR,
		(volatile uint8_t *)SCI0_TDR_ADDR,
		(volatile uint8_t *)SCI0_RDR_ADDR,
		(volatile uint8_t *)SCI0_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI0_SSR_ADDR,
		INT_SCI0_TXI0,
		INT_SCI0_RXI0,
		INT_SCI0_TEI0,
		0,
		SYSTEM_MSTPCRB_MSTPB31_BIT,
	} ,			/* UART0 */
#if TNUM_SIOP > 1
	{
		(volatile uint8_t *)SCI1_SCR_ADDR,
		(volatile uint8_t *)SCI1_SMR_ADDR,
		(volatile uint8_t *)SCI1_SEMR_ADDR,
		(volatile uint8_t *)SCI1_SSR_ADDR,
		(volatile uint8_t *)SCI1_TDR_ADDR,
		(volatile uint8_t *)SCI1_RDR_ADDR,
		(volatile uint8_t *)SCI1_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI1_SSR_ADDR,
		INT_SCI1_TXI1,
		INT_SCI1_RXI1,
		INT_SCI1_TEI1,
		1,
		SYSTEM_MSTPCRB_MSTPB30_BIT,
	} ,			/* UART1 */
#endif
#if TNUM_SIOP > 2
	{
		(volatile uint8_t *)SCI2_SCR_ADDR,
		(volatile uint8_t *)SCI2_SMR_ADDR,
		(volatile uint8_t *)SCI2_SEMR_ADDR,
		(volatile uint8_t *)SCI2_SSR_ADDR,
		(volatile uint8_t *)SCI2_TDR_ADDR,
		(volatile uint8_t *)SCI2_RDR_ADDR,
		(volatile uint8_t *)SCI2_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI2_SSR_ADDR,
		INT_SCI2_TXI2,
		INT_SCI2_RXI2,
		INT_SCI2_TEI2,
		2,
		SYSTEM_MSTPCRB_MSTPB29_BIT,
	} ,			/* UART2 */
#endif
#if TNUM_SIOP > 3
	{
		(volatile uint8_t *)SCI3_SCR_ADDR,
		(volatile uint8_t *)SCI3_SMR_ADDR,
		(volatile uint8_t *)SCI3_SEMR_ADDR,
		(volatile uint8_t *)SCI3_SSR_ADDR,
		(volatile uint8_t *)SCI3_TDR_ADDR,
		(volatile uint8_t *)SCI3_RDR_ADDR,
		(volatile uint8_t *)SCI3_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI3_SSR_ADDR,
		INT_SCI3_TXI3,
		INT_SCI3_RXI3,
		INT_SCI3_TEI3,
		3,
		SYSTEM_MSTPCRB_MSTPB28_BIT,
	} ,			/* UART3 */
#endif
#if TNUM_SIOP > 4
	{
		(volatile uint8_t *)SCI4_SCR_ADDR,
		(volatile uint8_t *)SCI4_SMR_ADDR,
		(volatile uint8_t *)SCI4_SEMR_ADDR,
		(volatile uint8_t *)SCI4_SSR_ADDR,
		(volatile uint8_t *)SCI4_TDR_ADDR,
		(volatile uint8_t *)SCI4_RDR_ADDR,
		(volatile uint8_t *)SCI4_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI4_SSR_ADDR,
		INT_SCI4_TXI4,
		INT_SCI4_RXI4,
		INT_SCI4_TEI4,
		4,
		SYSTEM_MSTPCRB_MSTPB27_BIT,
	} ,		/* UART4 */
#endif
#if TNUM_SIOP > 5
	{
		(volatile uint8_t *)SCI5_SCR_ADDR,
		(volatile uint8_t *)SCI5_SMR_ADDR,
		(volatile uint8_t *)SCI5_SEMR_ADDR,
		(volatile uint8_t *)SCI5_SSR_ADDR,
		(volatile uint8_t *)SCI5_TDR_ADDR,
		(volatile uint8_t *)SCI5_RDR_ADDR,
		(volatile uint8_t *)SCI5_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI5_SSR_ADDR,
		INT_SCI5_TXI5,
		INT_SCI5_RXI5,
		INT_SCI5_TEI5,
		5,
		SYSTEM_MSTPCRB_MSTPB26_BIT,
	} ,		/* UART5 */
#endif
#if TNUM_SIOP > 6
	{
		(volatile uint8_t *)SCI6_SCR_ADDR,
		(volatile uint8_t *)SCI6_SMR_ADDR,
		(volatile uint8_t *)SCI6_SEMR_ADDR,
		(volatile uint8_t *)SCI6_SSR_ADDR,
		(volatile uint8_t *)SCI6_TDR_ADDR,
		(volatile uint8_t *)SCI6_RDR_ADDR,
		(volatile uint8_t *)SCI6_BRR_ADDR,
		(volatile uint32_t *)SYSTEM_MSTPCRB_ADDR,
		(volatile uint8_t *)SCI6_SSR_ADDR,
		INT_SCI6_TXI6,
		INT_SCI6_RXI6,
		INT_SCI6_TEI6,
		6,
		SYSTEM_MSTPCRB_MSTPB25_BIT,
	} ,		/* UART6 */
#endif
};

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */
#define INDEX_SIOP(siopid)	 ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	 (&(siopcb_table[INDEX_SIOP(siopid)]))
#define get_siopinib(siopid) (&(siopinib_table[INDEX_SIOP(siopid)]))


/*
 *  SIOドライバのシリアルモードレジスタ(SMR)
 */
static void
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

	/*
	 *  モジュールストップ機能の設定(SCI1)
	 */
	sil_wrw_mem((void *)p_siopinib->mstpcrreg, (~p_siopinib->mstpcr_offset));

	/* 送受信禁止, SCKn端子は入出力ポートとして使用 */
	sil_wrb_mem((void *)p_siopinib->ctlreg, 0x00U);

	/* クロック選択ビット(SMR.CKS[1:0]ビットを設定) */
	sil_wrb_mem((void *)p_siopinib->modereg, 
					sil_reb_mem((void *)p_siopinib->modereg) | clksrc);

	/* SMRに送信／ 受信フォーマットを設定) */
	sil_wrb_mem((void *)p_siopinib->modereg, 
			sil_reb_mem((void *)p_siopinib->modereg) & (~SCI_SMR_FLG_ENABLE));

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
 *  SIOドライバの初期化ルーチン
 */
void
scic_uart_initialize(void)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++){
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
	}
}

/*
 *  カーネル起動時のバナー出力用の初期化
 */
void
scic_uart_init(ID siopid, uint8_t bitrate, uint8_t clksrc)
{
	SIOPCB          *p_siopcb   = get_siopcb(siopid);
	const SIOPINIB  *p_siopinib = get_siopinib(siopid);
	/*  この時点では、p_siopcb->p_siopinibは初期化されていない  */

	/*  二重初期化の防止  */
	p_siopcb->is_initialized = true;

	/*  ハードウェアの初期化処理と送信許可  */
	scic_uart_setmode(p_siopinib , bitrate, clksrc);
	sil_wrb_mem((void *)p_siopinib->ctlreg, 
					(uint8_t)(sil_reb_mem((void *)p_siopinib->ctlreg) | TE));
}


/*
 *  シリアルI/Oポートへのポーリングでの出力
 */
void
scic_uart_pol_putc(char c, ID siopid)
{
	const SIOPINIB *p_siopinib;

	p_siopinib = get_siopinib(siopid);

	/*
	 *  送信レジスタが空になるまで待つ
	 */
	while((sil_reb_mem(
			(void *)p_siopinib->ssrreg) & SCI_SSR_TEND_BIT) == 0U);

	sil_wrb_mem((void *)p_siopinib->tdreg, (uint8_t)c);
}

/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *
scic_uart_opn_por
	(ID siopid, intptr_t exinf, uint8_t bitrate, uint8_t clksrc)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;

	p_siopcb = get_siopcb(siopid);
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

    return (p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
scic_uart_cls_por(SIOPCB *p_siopcb)
{
	/*
	 *  UART停止
	 */
	sil_wrh_mem((void *)p_siopcb->p_siopinib->ctlreg, 0x00U);
	p_siopcb->openflag = false;
	p_siopcb->is_initialized = false;
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t
scic_uart_snd_chr(SIOPCB *p_siopcb, char c)
{
	bool_t ercd = false;

	if((sil_reb_mem(
		(void *)p_siopcb->p_siopinib->ssrreg) & SCI_SSR_TEND_BIT) != 0){
		sil_wrb_mem((void *)p_siopcb->p_siopinib->tdreg, (uint8_t)c);
		ercd = true;
	}

	return ercd;
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
scic_uart_rcv_chr(SIOPCB *p_siopcb)
{
	int_t c = -1;

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
scic_uart_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
		case SIO_RDY_SND:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) | SCI_SCR_TEIE_BIT));
			break;
		case SIO_RDY_RCV:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) | SCI_SCR_RIE_BIT));
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
scic_uart_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
		case SIO_RDY_SND:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) & (~SCI_SCR_TEIE_BIT)));
			break;
		case SIO_RDY_RCV:
			sil_wrb_mem((void *)p_siopcb->p_siopinib->ctlreg, 
				(sil_reb_mem((void *)p_siopcb->p_siopinib->ctlreg) & (~SCI_SCR_RIE_BIT)));
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
scic_uart_tx_isr(ID siopid)
{
	SIOPCB	*p_siopcb = get_siopcb(siopid);

	if((sil_reb_mem(
		(void *)p_siopcb->p_siopinib->ssrreg) & SCI_SSR_TEND_BIT) != 0U){
		/*
		 *  送信可能コールバックルーチンを呼び出す．
		 */
		scic_uart_irdy_snd(p_siopcb->exinf);
	}
}

void
scic_uart_rx_isr(ID siopid)
{
	SIOPCB	*p_siopcb = get_siopcb(siopid);

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

