/*
 *  TINET (TCP/IP Protocol Stack)
 *
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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

/*
 *  ターゲット依存モジュール（RX64M用）
 */

#include <sil.h>

#if defined(SUPPORT_ETHER)

#include <tinet_defs.h>
#include <tinet_config.h>
#include "target_board.h"
#include <target_device/target_device.h>


/*
 *  edmac_bus_init -- ターゲット依存部のバスの初期化
 */

void
edmac_bus_init (void)
{
	/* イーサネット・コントローラの動作を許可 */
	sil_wrh_mem((uint16_t *)SYSTEM_PRCR_ADDR, (uint16_t)0xA502);	/* 書込み許可 */
	sil_wrw_mem((uint32_t *)SYSTEM_MSTPCRB_ADDR,
		sil_rew_mem((uint32_t *)SYSTEM_MSTPCRB_ADDR) & ~SYSTEM_MSTPCRB_MSTPB15_ETH0);
	sil_wrh_mem((uint16_t *)SYSTEM_PRCR_ADDR, (uint16_t)0xA500);	/* 書込み禁止 */

	/* EtherNET有効 */
	/* P71-72, P74-77 RMII_MDIO, RMII_MDC,RXD1, RXD0, REF50CK, RX-ER */
	sil_wrb_mem((uint8_t *)PORT7_PMR_ADDR,
		sil_reb_mem((uint8_t *)PORT7_PMR_ADDR) | 0xF6);
	/* P80〜3 TXD-EN, TXD0, TXD1, CRS */
	sil_wrb_mem((uint8_t *)PORT8_PMR_ADDR,
		sil_reb_mem((uint8_t *)PORT8_PMR_ADDR) | 0x0F);

	/* 書き込みプロテクトレジスタの設定 PFSWEビットへの書き込みを許可 */
	sil_wrb_mem((uint8_t *)(MPC_PWPR_ADDR) , 0x00);
	/* 書き込みプロテクトレジスタの設定 PxxFSレジスタへの書き込みを許可 */
	sil_wrb_mem((uint8_t *)(MPC_PWPR_ADDR) , 0x40);

	/* P71をET_MDIOとする */
	sil_wrb_mem((uint8_t *)MPC_P71PFS_ADDR, 0x11);
	/* P72をET_MDCとする */
	sil_wrb_mem((uint8_t *)MPC_P72PFS_ADDR, 0x11);
    //	/* PA5をET_LINKSTAとする */
    //	sil_wrb_mem((uint8_t *)MPC_PA5PFS_ADDR, 0x11);

	/* P74をRXD1とする */
	sil_wrb_mem((uint8_t *)MPC_P74PFS_ADDR, 0x12);
	/* P75をRXD0とする */
	sil_wrb_mem((uint8_t *)MPC_P75PFS_ADDR, 0x12);
	/* P76をREF50CKとする */
	sil_wrb_mem((uint8_t *)MPC_P76PFS_ADDR, 0x12);
	/* P77をRX-ERとする */
	sil_wrb_mem((uint8_t *)MPC_P77PFS_ADDR, 0x12);
	/* P80をTXD-ENとする */
	sil_wrb_mem((uint8_t *)MPC_P80PFS_ADDR, 0x12);
	/* P81をTXD0とする */
	sil_wrb_mem((uint8_t *)MPC_P81PFS_ADDR, 0x12);
	/* P82をTXD1とする */
	sil_wrb_mem((uint8_t *)MPC_P82PFS_ADDR, 0x12);
	/* P83をCRSとする */
	sil_wrb_mem((uint8_t *)MPC_P83PFS_ADDR, 0x12);

	/* 書き込みプロテクトレジスタの設定 書き込みを禁止 */
	sil_wrb_mem((uint8_t *)(MPC_PWPR_ADDR) , 0x80);
}

/*
 *  rx62n_inter_init -- ターゲット依存部の割込みの初期化
 */

#ifdef USE_EPTPC_0
#include <driver/rx_gcc/EPTPC.h>

extern uint8_t mac_addr[6];
#endif


void
edmac_inter_init (void)
{

}


#ifdef USE_EPTPC_0
#include <driver/rx_gcc/EPTPC.h>

extern uint8_t target_ptp_mode;
extern uint8_t mac_addr[6];
extern PTPINI ptp_conf;
#endif


void
edmac_hard_init_hook (void)
{
#ifdef USE_EPTPC_0
  PTPINI* ptp_stat;
  ptp_stat = (PTPINI*)GET_DEV_STAT(DEV_EPTPC0);
  
  eptpc_target_config(mac_addr,
                      ptp_stat->sys->ipclk_conf,
                      ptp_stat->sys->stca_sel,
                      ptp_stat->port->ptp_mode
                      ) ;
  eptpc_init(ptp_stat);
#endif
}

#endif	/* of #if defined(SUPPORT_ETHER) */

