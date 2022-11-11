/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <sil.h>
#include <kernel_cfg.h>
#include <driver/rx_gcc/SCIg.h>
#include <target_board.h>

#ifdef USE_SCIG_0

static const SIOPINIB siopinib_table_0 = {
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_SCR_OFFSET), 
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_SMR_OFFSET),
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_SEMR_OFFSET),
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_SSR_OFFSET),
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_TDR_OFFSET),
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_RDR_OFFSET),
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_BRR_OFFSET),
  (volatile uint8_t *)(SCI0_BASE_ADDR + SCIG_SSR_OFFSET),
  INT_SCI0_TXI0,
  INT_SCI0_RXI0,
  0,
  0
};

SIOPCB siopcb_table_0 = {
  &siopinib_table_0, //SIOPINIB *
  0,   //intptr_t exinf
  false, //bool_t openflag
  false, //bool_t sendflag
  false, //bool_t getready
  false, //bool_t putready
  false  // bool_t is_initialized
};
  

dev_node_t scig_node_0 = {
  NULL,
  &siopcb_table_0
};

void
target_dev_ini_scig_0( void )
{
  //unlock register access 
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);
  /*
   * モジュールストップ機能の設定(SCI2)
   */
  *SYSTEM_MSTPCRB_ADDR &= ~(SYSTEM_MSTPCRB_MSTPB31_SCI0); /* SCI0 */
  //lock register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
  
  /* ポートP20をTxD0, ポートP21をRxD0に */
  /* MPC setting */
  /* unlock PFS write protection */
  sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
  sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSWE_BIT);
  /* p20 is set as TxD0 mode */
  sil_wrb_mem((void *)(MPC_P20PFS_ADDR), MPC_PFS_PSELA);
  /* p52 is set as RxD0 mode*/
  sil_wrb_mem((void *)(MPC_P21PFS_ADDR), MPC_PFS_PSELA);
  /* lock PFS write */
  sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
  sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_B0WI_BIT);

  /* port mode setting */
  /* Port Mode Register(PMR) config. P20(TxD0) and P21(RxD0) are setted to IP use */
  sil_wrb_mem((void *)(PORT2_PMR_ADDR) ,
				sil_reb_mem((void *)(PORT2_PMR_ADDR)) | PORT_PMR_B0_BIT | PORT_PMR_B1_BIT);
  /* pull up Tx, Rx port*/
  sil_wrb_mem((void *)(PORT2_PCR_ADDR),
		  sil_reb_mem((void *)(PORT2_PCR_ADDR)) | PORT_PCR_B0_BIT | PORT_PCR_B1_BIT);

}

#endif
