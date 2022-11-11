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
 *		タイマドライバ（RX72n 用）
 */
 
#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

#include <sil.h>
#include "target_board.h"
#include "target_syssvc.h"

/*
 *  タイマ割込みハンドラ登録のための定数
 */
#define INHNO_TIMER		INT_CMT0_CMI0		/* 割込みハンドラ番号 */
#define INTNO_TIMER		INT_CMT0_CMI0		/* 割込み番号 */
#define INHNO_TIMER_CMT1		INT_CMT1_CMI1		/* 割込みハンドラ番号 */
#define INTNO_TIMER_CMT1		INT_CMT1_CMI1		/* 割込み番号 */
#define INHNO_TIMER_CMT2		INT_CMT2_CMI2		/* 割込みハンドラ番号 */
#define INTNO_TIMER_CMT2		INT_CMT2_CMI2		/* 割込み番号 */

#define INTPRI_TIMER	-5					/* 割込み優先度 */
#define INTATR_TIMER	TA_ENAINT | TA_EDGE	/* 割込み属性 */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  タイマ値の内部表現の型
 */
typedef uint16_t	CLOCK;

/*
 *  タイマ値の内部表現とミリ秒単位との変換
 *
 *  1msのタイマー割り込みを使用するのでそのクロックを定義する．
 */
#define TIMER_CLOCK				(6000U)		/* 6.000MHz */
#define TO_CLOCK(nume, deno)	((CLOCK)(TIMER_CLOCK * (nume) / (deno)))
#define	TO_USEC(clock)			((SYSUTM)((clock) * 1000U / TIMER_CLOCK))

#define RX72N_PCLK 				(60000000) // Renesas BSP Setting PCLK
#define RX72N_PCLK_CKS 			(32) // Renesas BSP Setting PCLK CKS
#define RX72N_PCLK_DIV 			(100) // divide value (10msec)

#define RX72N_CMCOR			    ((unsigned short)(RX72N_PCLK / RX72N_PCLK_CKS / RX72N_PCLK_DIV) - 1)
/*
 *  設定できる最大のタイマ周期（単位は内部表現）
 */
#define	MAX_CLOCK	((CLOCK) 0xFFFFU)

/*
 *  性能評価用システム時刻を取り出す際の処理時間の見積り値（単位は内部表現）
 */
#define	GET_TOLERANCE	(100U)	/* 処理遅れの見積り値（単位は内部表現）*/
#define	BEFORE_IREQ(clock) \
		((clock) >= (TO_CLOCK(TIC_NUME, TIC_DENO) - GET_TOLERANCE))

/*
 *  コンペアマッチタイマコントロールレジスタの設定値
 */
/*
 *  クロック選択ビット
 *
 *  bit7は予約領域であり, 書込みは1固定
 */
#define CMT_PCLK_DIV_8			(0x0080U)
#define CMT_PCLK_DIV_32			(0x0081U)
#define CMT_PCLK_DIV_128		(0x0082U)
#define CMT_PCLK_DIV_512		(0x0083U)

/*
 *  コンペアマッチタイマコンスタントレジスタ（CMCOR）
 *
 *  コンペアマッチ周期を1msとする．
 *  周辺モジュールクロック（PCLK）48MHzを8分周するので，
 *  1周期あたり166.6nsecとなり，6000周期で1ms（タイムティックの周期）とする．
 */
#define CMCOR_PERIOD			(6000U)

/*
 * コンペアマッチタイマ割り込み要求先設定レジスタi（ISELRi）（i= 割り込みベクタ番号）
 */
#define ICU_ISEL_CPU			(0x00U)


/*
 *	ターゲットシステム依存モジュール（RX72N用 Timer (CMT0) Interrupt Wrapper）
 */

extern void timer_int_Wrapper();


/*
 *  タイマの起動処理
 *
 *  タイマを初期化し，周期的なタイマ割込み要求を発生させる．
 */
extern void	target_timer_initialize(intptr_t exinf);
extern void	target_timer_cmt1_initialize(intptr_t exinf);
extern void	target_timer_cmt2_initialize(intptr_t exinf);

/*
 *  タイマの停止処理
 *
 *  タイマの動作を停止させる．
 */
extern void	target_timer_terminate(intptr_t exinf);
extern void	target_timer_cmt1_terminate(intptr_t exinf);
extern void	target_timer_cmt2_terminate(intptr_t exinf);

/*
 *  タイマレジスタ値の読み出し
 */
Inline uint16_t rx72n_cmt_getcount(void)
{
	return *CMT0_CMCNT_ADDR;
}

/*
 *  タイマレジスタ値の書き込み
 */
Inline void rx72n_cmt_setcount(uint16_t count)
{
	*CMT0_CMCNT_ADDR = count;
}

/*
 *  タイマの現在値の読出し
 */
Inline CLOCK
target_timer_get_current(void)
{
	/* アップカウントのためタイマレジスタ値をそのまま返す	*/
	return (rx72n_cmt_getcount());
}

/*
 *  タイマ割込み要求のチェック
 */
Inline bool_t
target_timer_probe_int(void)
{
	return(x_probe_int(INTNO_TIMER));
}

/*
 *  タイマ割込みハンドラ
 */
extern void	target_timer_handler(void);
extern void	target_timer_cm1_handler(void);
extern void	target_timer_cm2_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_TIMER_H */
