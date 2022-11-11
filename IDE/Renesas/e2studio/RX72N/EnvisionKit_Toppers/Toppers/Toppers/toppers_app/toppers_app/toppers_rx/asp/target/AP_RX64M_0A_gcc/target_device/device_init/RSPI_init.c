/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <kernel_cfg.h>
#include <target_device/device_init/RSPI_init.h>
#include <driver/rx_gcc/RSPI.h>

#define RSPI_CH0_BASE 0x000D0100

#ifdef USE_RSPI_0

rspi_dstat rspi_st_0 = {
  RSPI_CH0_BASE,
  0,
  RSPI_0_RX_INT_NO,
  RSPI_0_TX_INT_NO,
  RSPI_0_IP_LOCK_SEM,
  RSPI_0_INT_SYNC_SEM
};

const dev_node_t rspi_node_0 = {
  NULL,
  (void*)&rspi_st_0
};

void target_dev_ini_rspi_0(){
	uint8_t rd;
    /* power management setting*/
	/* unlock register access */
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

	//enable RSPI0
	*SYSTEM_MSTPCRB_ADDR &= ~(SYSTEM_MSTPCRB_MSTPB17_RSPI0); /* RSPI0 */
	//lock register access
	sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
	/* end power management setting */


	/* MPC setting (change multi function pin mode to IP use)*/
	/* unlock PFS write protection */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSWE_BIT);
	/* pc0 is set as SPI mode */
	sil_wrb_mem((void *)(MPC_PC5PFS_ADDR), MPC_PFS_PSELD);
	sil_wrb_mem((void *)(MPC_PC6PFS_ADDR), MPC_PFS_PSELD);
	sil_wrb_mem((void *)(MPC_PC7PFS_ADDR), MPC_PFS_PSELD);
    
	/* lock PFS write */
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_PFSW_CLEAR);
	sil_wrb_mem((void *)(MPC_PWPR_ADDR), MPC_PWPR_B0WI_BIT);

	//set pmr register(select io pins to use SPI)
	rd = sil_reb_mem(PORTC_PMR_ADDR);
	sil_wrb_mem(PORTC_PMR_ADDR, rd | PORT_PMR_B5_BIT | PORT_PMR_B6_BIT | PORT_PMR_B7_BIT);

}
#endif

