/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *		ターゲット依存モジュール（GR-SAKURA用）
 *
 *  カーネルのターゲット依存部のインクルードファイル．kernel_impl.hのター
 *  ゲット依存部の位置付けとなる．
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  ターゲットシステムのハードウェア資源の定義
 */
#include "target_board.h"


/*
 *  デフォルトの非タスクコンテキスト用のスタック領域の定義
 *
 *  スタックサイズを変更する場合は, sectrx.incの_DEFAULT_ISTACK
 *  ラベルの位置にある.blkb命令のサイズと, 以下DEFAULT_ISTKSZの
 *  サイズを合わせて同じ値に変更すること.
 */

#ifndef TOPPERS_MACRO_ONLY
extern uint32_t	DEFAULT_ISTACK[];
#endif

#define DEFAULT_ISTKSZ		(0x10000U) //( 0x1e00CU ) //wata
#define DEFAULT_ISTK		( (void *)&DEFAULT_ISTACK[0] )


/*
 *  ターゲット依存の文字出力に使用するポートの定義
 */
#define TARGET_PUTC_PORTID	( 1 )


#ifndef TOPPERS_MACRO_ONLY

/*
 *  ターゲットシステム依存の初期化
 */
extern void	target_initialize( void );

/*
 *  ターゲットシステムの終了
 *
 *  システムを終了する時に使う．
 */
extern void	target_exit( void )	NoReturn;

#endif /* TOPPERS_MACRO_ONLY */


/*
 *  プロセッサ依存モジュール（RX63n用）
 */
#include "rx63n_config.h"


/*
 *  トレースログに関する設定
 */
#define TCNT_TRACE_BUFFER	( 32 )

/*
 *  トレースログ出力する箇所の選択
 *    ログ出力する箇所を1で定義
 *    ログ出力しない箇所を0で定義
 */
#ifdef TOPPERS_ENABLE_TRACE
#define LOG_DSP_ENTER	( 1 )
#define LOG_DSP_LEAVE	( 1 )
#define LOG_INH_ENTER	( 0 )
#define LOG_INH_LEAVE	( 0 )
#define LOG_EXC_ENTER	( 0 )
#define LOG_EXC_LEAVE	( 0 )
#else
#define LOG_DSP_ENTER	( 0 )
#define LOG_DSP_LEAVE	( 0 )
#define LOG_INH_ENTER	( 0 )
#define LOG_INH_LEAVE	( 0 )
#define LOG_EXC_ENTER	( 0 )
#define LOG_EXC_LEAVE	( 0 )
#endif

#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

#endif /* TOPPERS_TARGET_CONFIG_H */
