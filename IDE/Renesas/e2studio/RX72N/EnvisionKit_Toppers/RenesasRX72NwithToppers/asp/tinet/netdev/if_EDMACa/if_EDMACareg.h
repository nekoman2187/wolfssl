/*
 *  TINET (TCP/IP Protocol Stack)
 *
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2014-2015 Cores Co., Ltd. Japan
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
 *  @(#) $Id$
 */

#ifndef EDMACRegH
#define EDMACRegH

#include "t_stddef.h"
#include <target_board.h>

#define EDMAC_EDMR			((uint32_t *)(TINET_EDMAC_BASE + 0x0))	/* EDMACモードレジスタ */
#define EDMAC_EDMR_SWR_BIT	0x00000001
#define EDMAC_EDMR_DE_BIT	0x00000040

#define EDMAC_EDTRR			((uint32_t *)(TINET_EDMAC_BASE + 0x8))	/* EDMAC送信要求レジスタ */
#define EDMAC_EDTRR_TR		0x00000001

#define EDMAC_EDRRR			((uint32_t *)(TINET_EDMAC_BASE + 0x10))	/* EDMAC受信要求レジスタ */
#define EDMAC_EDRRR_RR		0x00000001

#define EDMAC_TDLAR			((uint32_t *)(TINET_EDMAC_BASE + 0x18))	/* 送信ディスクリプタリスト先頭アドレスレジスタ */
#define EDMAC_RDLAR			((uint32_t *)(TINET_EDMAC_BASE + 0x20))	/* 受信ディスクリプタリスト先頭アドレスレジスタ */

#define EDMAC_EESR			((uint32_t *)(TINET_EDMAC_BASE + 0x28))	/* ETHERC/EDMACステータスレジスタ */
#define EDMAC_EESR_FROF		0x00010000
#define EDMAC_EESR_RDE		0x00020000
#define EDMAC_EESR_FR		0x00040000
#define EDMAC_EESR_TFUF     0x00080000
#define EDMAC_EESR_TC		0x00200000
#define EDMAC_EESR_TWB		0x40000000

#define EDMAC_EESIPR		((uint32_t *)(TINET_EDMAC_BASE + 0x30))	/* ETHERC/EDMACステータス割り込み許可レジスタ */
#define EDMAC_EESIPR_RMAFIP	0x00000080
#define EDMAC_EESIPR_FROFIP	0x00010000
#define EDMAC_EESIPR_RDEIP	0x00020000
#define EDMAC_EESIPR_FRIP	0x00040000
#define EDMAC_EESIPR_TFUFIP 0x00080000
#define EDMAC_EESIPR_TCIP	0x00200000
#define EDMAC_EESIPR_TWBIP	0x40000000

#define EDMAC_TRSCER		((uint32_t *)(TINET_EDMAC_BASE + 0x38))	/* 送受信ステータスコピー指示レジスタ */
#define EDMAC_RMFCR			((uint32_t *)(TINET_EDMAC_BASE + 0x40))	/* ミスドフレームカウンタレジスタ */
#define EDMAC_TFTR			((uint32_t *)(TINET_EDMAC_BASE + 0x48))	/* 送信FIFOしきい値指定レジスタ */
#define EDMAC_FDR			((uint32_t *)(TINET_EDMAC_BASE + 0x50))	/* FIFO容量指定レジスタ */
#define EDMAC_RMCR			((uint32_t *)(TINET_EDMAC_BASE + 0x58))	/* 受信方式制御レジスタ */
#define EDMAC_TFUCR			((uint32_t *)(TINET_EDMAC_BASE + 0x64))	/* 送信FIFOアンダランカウント */
#define EDMAC_RFOCR			((uint32_t *)(TINET_EDMAC_BASE + 0x68))	/* 受信FIFOオーバフローカウント */
#define EDMAC_IOSR			((uint32_t *)(TINET_EDMAC_BASE + 0x6C))	/* 個別出力信号設定レジスタ */
#define EDMAC_FCFTR			((uint32_t *)(TINET_EDMAC_BASE + 0x70))	/* フロー制御開始FIFOしきい値設定レジスタ */
#define EDMAC_RPADIR		((uint32_t *)(TINET_EDMAC_BASE + 0x78))	/* 受信データパディング挿入設定レジスタ */
#define EDMAC_TRIMD			((uint32_t *)(TINET_EDMAC_BASE + 0x7C))	/* 送信割り込み設定レジスタ */
#define EDMAC_RBWAR			((uint32_t *)(TINET_EDMAC_BASE + 0xC8))	/* 受信バッファライトアドレスレジスタ */
#define EDMAC_RDFAR			((uint32_t *)(TINET_EDMAC_BASE + 0xCC))	/* 受信ディスクリプタフェッチアドレスレジスタ */
#define EDMAC_TBRAR			((uint32_t *)(TINET_EDMAC_BASE + 0xD4))	/* 送信バッファリードアドレスレジスタ */
#define EDMAC_TDFAR			((uint32_t *)(TINET_EDMAC_BASE + 0xD8))	/* 送信ディスクリプタフェッチアドレスレジスタ */

#define ETHERC_ECMR			((uint32_t *)(TINET_ETHERC_BASE + 0x0))	/* ETHERCモードレジスタ */
#define ETHERC_ECMR_PRM		0x00000001
#define ETHERC_ECMR_DM		0x00000002
#define ETHERC_ECMR_RTM		0x00000004
#define ETHERC_ECMR_TE		0x00000020
#define ETHERC_ECMR_RE		0x00000040

#define ETHERC_RFLR			((uint32_t *)(TINET_ETHERC_BASE + 0x8))	/* 受信フレーム長上限レジスタ */
#define ETHERC_ECSR			((uint32_t *)(TINET_ETHERC_BASE + 0x10))	/* ETHERCステータスレジスタ */
#define ETHERC_ECSR_LCHNG	0x00000004
#define ETHERC_ECSIPR		((uint32_t *)(TINET_ETHERC_BASE + 0x18))	/* ETHERC割り込み許可レジスタ */
#define ETHERC_ECSIPR_LCHNGIP	0x00000004
#define ETHERC_PIR			((uint32_t *)(TINET_ETHERC_BASE + 0x20))	/* PHY部インタフェースレジスタ */
#define ETHERC_PIR_MDC		0x00000001
#define ETHERC_PIR_MMD		0x00000002
#define ETHERC_PIR_MDO		0x00000004
#define ETHERC_PIR_MDI		0x00000008

#define ETHERC_PSR			((uint32_t *)(TINET_ETHERC_BASE + 0x28))	/* PHY部ステータスレジスタ */
#define ETHERC_PSR_LMON		0x00000001

#define ETHERC_RDMLR		((uint32_t *)(TINET_ETHERC_BASE + 0x40))	/* 乱数生成カウンタ上限値設定レジスタ */
#define ETHERC_IPGR			((uint32_t *)(TINET_ETHERC_BASE + 0x50))	/* IPG設定レジスタ */
#define ETHERC_APR			((uint32_t *)(TINET_ETHERC_BASE + 0x54))	/* 自動PAUSEフレーム設定レジスタ */
#define ETHERC_MPR			((uint32_t *)(TINET_ETHERC_BASE + 0x58))	/* 手動PAUSEフレーム設定レジスタ */
#define ETHERC_RFCF			((uint32_t *)(TINET_ETHERC_BASE + 0x60))	/* 受信PAUSEフレームカウンタ */
#define ETHERC_TPAUSER		((uint32_t *)(TINET_ETHERC_BASE + 0x64))	/* 自動PAUSEフレーム再送回数設定レジスタ */
#define ETHERC_TPAUSECR		((uint32_t *)(TINET_ETHERC_BASE + 0x68))	/* PAUSEフレーム再送回数カウンタ */
#define ETHERC_BCFRR		((uint32_t *)(TINET_ETHERC_BASE + 0x6C))	/* Broadcastフレーム受信回数設定レジスタ */
#define ETHERC_MAHR			((uint32_t *)(TINET_ETHERC_BASE + 0xC0))	/* MACアドレス上位設定レジスタ */
#define ETHERC_MALR			((uint32_t *)(TINET_ETHERC_BASE + 0xC8))	/* MACアドレス下位設定レジスタ */
#define ETHERC_TROCR		((uint32_t *)(TINET_ETHERC_BASE + 0xD0))	/* 送信リトライオーバカウンタレジスタ */
#define ETHERC_CDCR			((uint32_t *)(TINET_ETHERC_BASE + 0xD4))	/* 遅延衝突検出カウンタレジスタ */
#define ETHERC_LCCR			((uint32_t *)(TINET_ETHERC_BASE + 0xD8))	/* キャリア消失カウンタレジスタ */
#define ETHERC_CNDCR		((uint32_t *)(TINET_ETHERC_BASE + 0xDC))	/* キャリア未検出カウンタレジスタ */
#define ETHERC_CEFCR		((uint32_t *)(TINET_ETHERC_BASE + 0xE4))	/* CRCエラーフレーム受信カウンタレジスタ */
#define ETHERC_FRECR		((uint32_t *)(TINET_ETHERC_BASE + 0xE8))	/* フレーム受信エラーカウンタレジスタ */
#define ETHERC_TSFRCR		((uint32_t *)(TINET_ETHERC_BASE + 0xEC))	/* 64バイト未満フレーム受信カウンタレジスタ */
#define ETHERC_TLFRCR		((uint32_t *)(TINET_ETHERC_BASE + 0xF0))	/* 指定バイト超フレーム受信カウンタレジスタ */
#define ETHERC_RFCR			((uint32_t *)(TINET_ETHERC_BASE + 0xF4))	/* 端数ビットフレーム受信カウンタレジスタ */
#define ETHERC_MAFCR		((uint32_t *)(TINET_ETHERC_BASE + 0xF8))	/* マルチキャストアドレスフレーム受信カウンタレジスタ */

/* 送信ディスクリプタ */
typedef struct t_edmac_tx_desc {
  uint32_t	tfs : 26;
  uint32_t	twbi : 1;
  uint32_t	tfe : 1;
  uint32_t	tfp : 2;
  uint32_t	tdle : 1;
  uint32_t	tact : 1;
  uint32_t	reserved : 16;
  uint32_t	tbl : 16;
  uint32_t	tba;
  uint32_t	next; //use padding filed as next discripter address
} T_EDMAC_TX_DESC;

#define TX_TBL_PAGE_START_FLG 0x2
#define TX_TBL_PAGE_END_FLG 0x1
#define TX_TBL_SINGLE_PAGE 0x3

/* 受信ディスクリプタ */
typedef struct t_edmac_rx_desc {
	uint32_t	rfs : 27;
	uint32_t	rfe : 1;
	uint32_t	rfp : 2;
	uint32_t	rdle : 1;
	uint32_t	ract : 1;
	uint32_t	rfl : 16;
	uint32_t	rbl : 16;
	uint32_t	rba;
	uint32_t	next; //use padding filed as next discripter address
} T_EDMAC_RX_DESC;

#define RX_RFP_PAGE_START_FLG 0x2
#define RX_RFP_PAGE_END_FLG 0x1
#define RX_RFP_SINGLE_PAGE 0x3

#endif /* EDMACRegH */
