/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include <middleware/include/ff.h>
#include <target_board.h>

FATFS FatFs;

uint32_t buf[128], buf_2[128];

//define driver id of fatfs drive
const dnode_id pdrv_to_dev[1] = {
  DEV_MMC_RSPI0 //drive 1 is mmc_rspi
};

void main_task(intptr_t exinf)
{
  FIL fil;
  uint32_t i, res_b, comp_result;
  FRESULT fr;

  //create mount point
  for(i=0; i<128;i++) buf[i] = i;
  fr = f_mount(&FatFs, "", 0);

  //write test
  //open test file
  fr = f_open(&fil, "test.bin", FA_CREATE_ALWAYS|FA_WRITE|FA_READ);
  if (fr) return (int)fr;
  //write data
  f_write(&fil, buf, 512, res_b);
  
  f_lseek(&fil, 0);
  //read test
  for(i=0; i<128; i++) buf_2[i] = 0;
  f_read(&fil, buf_2, 512, res_b);

  f_close(&fil);
  // release mount point
  f_mount(NULL, "", 0);

  comp_result=0;
  for(i=0;i<128;i++)
    if(buf_2[i] != i)
      comp_result = -1;

  if(comp_result)
    assert(0);
}
