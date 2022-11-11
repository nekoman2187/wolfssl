/*
 * Copyright (c) 2017- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#include <kernel_impl.h>
//#include <sil.h>
//#include <target_board.h>
#include <driver/rx_gcc/EPTPC.h>

ER ptp_sync_monkey(){
  eptpc_reset();
  eptpc_init(PTPINI* pini);
  //not use w10(current version)
  //  set_w10_times();
  //trans mode condif if you need.
  //set_trans_mode();

  //EDMAC config if you need
  //edmac_config();

  //ptp_start
  ptp_syc_start(PTPINI* pini);
  //sync_if 290
}

