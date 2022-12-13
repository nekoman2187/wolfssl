/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#ifndef MMC_GPIO_DEF_H
#define MMC_GPIO_DEF_H

#include <target_board.h>


//rspi_mmc_node's status
typedef struct mmc_gpio_status_type{
  uint8_t *cd_pidr_baddr;
  uint8_t cd_bit_mask;
  uint8_t cd_bit_val;
  uint8_t *cs_podr_baddr;
  uint8_t cs_bit_mask;
} mmc_gpio_dstat;

uint8_t check_ins_sw(void*);
void select_gpio_cs(void *v_gpio_stat);
void deselect_gpio_cs(void *v_gpio_stat);

#endif
