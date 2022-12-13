/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <target_board.h>
#include <driver/rx_gcc/RSPI.h>
#include <driver/include/mmc_sdcard.h>

//mode switch
//  use dtc transfer
#define RSPI_MMC_DTCA_TRANS


//rspi_mmc_node's status
typedef struct mmc_rspi_dev_status_type{
  dnode_id mmc_drv_id;  //mmc driver id
  dnode_id mmc_ins_id;  //mmc card detect driver id
  DSTATUS Stat;
  uint8_t CardType;
  uint8_t tout_flg;
  ID tout_task_id_0;
  ID tout_task_id_1;
} mmc_rspi_stat_t;

//alarm handler
extern void disk_timerproc(intptr_t exinf);

//mmc_rspi_fucn is driver api.
//  refer from device node.
extern const mmc_func_t mmc_rspi_func;

//time out alarm handler
void mmc_rspi_tout0_handler(intptr_t exinf);
void mmc_rspi_tout1_handler(intptr_t exinf);


