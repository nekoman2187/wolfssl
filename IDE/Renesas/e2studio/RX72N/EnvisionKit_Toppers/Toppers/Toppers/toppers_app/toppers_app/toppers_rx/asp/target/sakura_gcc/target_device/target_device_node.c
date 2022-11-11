/*
 * Copyright (c) 2015- Hisashi Hata       
 * Released under the toppers license     
 * https://www.toppers.jp/license.html    
 */

#include <kernel.h>
#include <target_device/target_device.h>

#ifdef USE_RSPI_0
  extern dev_node_t rspi_node_0;
  void target_dev_ini_rspi_0();
#endif
#ifdef USE_MMC_RSPI_0
  extern dev_node_t mmc_sdcard_rspi_node_0;
  void target_dev_ini_mmc_sdcard_rspi_0();
#endif
#ifdef USE_MMC_GPIO_0
  extern dev_node_t mmc_sdcard_gpio_node_0;
  void target_dev_ini_mmc_sdcard_gpio_0();
#endif
#ifdef USE_DTCA_0
  extern dev_node_t _0;
  void target_dev_ini_dtca_0();
#endif
#ifdef USE_SCIC_0
  extern dev_node_t scic_node_0;
  void target_dev_ini_scic_0();
#endif

dev_info_t dev_info[NUM_TARGET_DEVICE] = {
  {0x0, NULL}, //NULL DEVICE
#ifdef USE_RSPI_0
  {0x0, &rspi_node_0},
#endif
#ifdef USE_MMC_RSPI_0
  {0x0, &mmc_sdcard_rspi_node_0},
#endif
#ifdef USE_MMC_GPIO_0
  {0x0, &mmc_sdcard_gpio_node_0},
#endif
#ifdef USE_DTCA_0
  {0x0, NULL},
#endif
#ifdef USE_SCIC_0
  {0x0, &scic_node_0}
#endif
};

void target_device_init(){
#ifdef USE_RSPI_0
  target_dev_ini_rspi_0();
#endif
#ifdef USE_MMC_RSPI_0
  target_dev_ini_mmc_sdcard_rspi_0();
#endif
#ifdef USE_MMC_GPIO_0
  target_dev_ini_mmc_sdcard_gpio_0();
#endif
#ifdef USE_DTCA_0
  target_dev_ini_dtca_0();
#endif
#ifdef USE_SCIC_0
  target_dev_ini_scic_0();
#endif
}
