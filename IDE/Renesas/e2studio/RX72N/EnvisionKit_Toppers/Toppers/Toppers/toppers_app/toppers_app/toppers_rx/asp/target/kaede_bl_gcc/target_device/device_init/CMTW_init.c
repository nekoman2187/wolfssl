/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <kernel_cfg.h>
#include <kernel_impl.h>
#include <target_device/target_device.h>

#ifdef USE_CMTW_0
#include <driver/rx_gcc/CMTW.h>

cmtw_dstat cmtw_stat_0 ={
  0x00094200
};

dev_node_t cmtw_node_0 = {
  NULL,
  (void*) &cmtw_stat_0
};


void target_dev_ini_cmtw_0(){
  /* power management setting*/
  /* unlock register access */
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

  //enable RSPI0
  *SYSTEM_MSTPCRA_ADDR &= ~(SYSTEM_MSTPCRA_MSTPA1_CMTW0); /* CMTW0 */
  //lock register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
  /* end power management setting */

  cmtw_init(DEV_CMTW0);
  config_cmwcr_count_mode(DEV_CMTW0,
                          CMWCR_CCLR_CLR_DIS
                          | CMWCR_CKS_DIV128
                          | CMWCR_CMS_32BIT);
  config_cmwcr_io_mode(DEV_CMTW0, 0);
}

#endif
