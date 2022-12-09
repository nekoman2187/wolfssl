/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#include <driver/rx_gcc/mmc_gpio.h>

//return sdcard status
//  not 0 : card is inserted
//  0     : card isn't inserted

uint8_t check_ins_sw(void *v_gpio_stat){
  mmc_gpio_dstat *gpio_stat;
  uint8_t io_val;
  gpio_stat = (mmc_gpio_dstat*)v_gpio_stat;
  io_val =sil_reb_mem(gpio_stat->cd_pidr_baddr);
  if((io_val & gpio_stat->cd_bit_mask) == gpio_stat->cd_bit_val)
	return 1;
  else
    return 0;
}

void deselect_gpio_cs(void *v_gpio_stat){
  mmc_gpio_dstat *gpio_stat;
  uint8_t current;
  gpio_stat = (mmc_gpio_dstat*)v_gpio_stat;
  current = sil_reb_mem(gpio_stat->cs_podr_baddr) | gpio_stat->cs_bit_mask;
  sil_wrb_mem(gpio_stat->cs_podr_baddr, current);
}

void select_gpio_cs(void *v_gpio_stat){
  mmc_gpio_dstat *gpio_stat;
  uint8_t current;
  gpio_stat = (mmc_gpio_dstat*)v_gpio_stat;
  current = sil_reb_mem(gpio_stat->cs_podr_baddr) & ~(gpio_stat->cs_bit_mask);
  sil_wrb_mem(gpio_stat->cs_podr_baddr, current);
}
