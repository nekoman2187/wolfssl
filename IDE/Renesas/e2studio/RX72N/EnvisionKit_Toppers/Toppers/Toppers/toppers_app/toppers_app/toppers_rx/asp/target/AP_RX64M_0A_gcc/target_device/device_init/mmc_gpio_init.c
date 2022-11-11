/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <driver/rx_gcc/mmc_gpio.h>
#include <target_device/target_device.h>


#ifdef USE_MMC_GPIO_0
mmc_gpio_dstat mmc_gpio_st_0 = {
  //card detect io define
  (uint8_t*)PORTC_PIDR_ADDR,
  PORT_PIDR_B3_BIT,
  0,  //io voltage is low when card inserted
  //card select io define
  (uint8_t*)PORTC_PODR_ADDR,
  PORT_PODR_B4_BIT
};

dev_node_t mmc_sdcard_gpio_node_0 = {
  NULL,
  &mmc_gpio_st_0
};

//GPIO Port 1-Bit 5 is Chip detect switch of SDCARD SROT
//  Set input gpio port
void target_dev_ini_mmc_sdcard_gpio_0(){
  uint8_t rd;
  //config CD pin
  //set input port
  rd = sil_reb_mem(PORTC_PDR_ADDR);
  sil_wrb_mem(PORTC_PDR_ADDR, rd & ~PORT_PDR_B3_BIT);
  //set gpio
  rd = sil_reb_mem(PORTC_PMR_ADDR);
  sil_wrb_mem(PORTC_PMR_ADDR, rd & ~PORT_PMR_B3_BIT);
  //config CS# pin
  //set output port
  rd = sil_reb_mem(PORTC_PDR_ADDR);
  sil_wrb_mem(PORTC_PDR_ADDR, rd | PORT_PDR_B4_BIT);
  //set gpio
  rd = sil_reb_mem(PORTC_PMR_ADDR);
  sil_wrb_mem(PORTC_PMR_ADDR, rd & ~PORT_PMR_B4_BIT);
  //unselect CS# pin
  //rd = sil_reb_mem(PORTC_PODR_ADDR);
  //sil_wrb_mem(PORTC_PODR_ADDR, rd | PORT_PODR_B4_BIT);

}
  
#endif
