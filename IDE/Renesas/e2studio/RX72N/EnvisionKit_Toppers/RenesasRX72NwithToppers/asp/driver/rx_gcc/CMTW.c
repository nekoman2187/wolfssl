/*
 * Copyright (c) 2018- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#include <kernel_impl.h>
#include <driver/rx_gcc/CMTW.h>
//#include <sil.h>
//#include <target_board.h>

#define CMTW_CMWSTR_OFFSET 0x0
#define CMTW_CMWCR_OFFSET 0x4
#define CMTW_CMWIOR_OFFSET 0x8
#define CMTW_CMWCNT_OFFSET 0x10
#define CMTW_CMWCOR_OFFSET 0x14
#define CMTW_CMWICR0_OFFSET 0x18
#define CMTW_CMWICR1_OFFSET 0x1C
#define CMTW_CMWOCR0_OFFSET 0x20
#define CMTW_CMWOCR1_OFFSET 0x24
//CMSTR
#define CMTW_CMWSTR_STR_BIT 0x1

static inline void write_cmtw_reg(dnode_id stat_id, uint32_t offset, uint16_t val){
  cmtw_dstat *cmtw_stat = (cmtw_dstat*)GET_DEV_STAT(stat_id);
  DEV_WRH(cmtw_stat->baddr, offset, val);
}

void cmtw_count_start(dnode_id stat_id){
  write_cmtw_reg(stat_id, CMTW_CMWSTR_OFFSET, CMTW_CMWSTR_STR_BIT);
}

void cmtw_count_stop(dnode_id stat_id){
  write_cmtw_reg(stat_id, CMTW_CMWSTR_OFFSET, 0);
}

void config_cmwcr_count_mode(dnode_id stat_id, uint16_t config_val){
  write_cmtw_reg(stat_id, CMTW_CMWCR_OFFSET, config_val);
}

void config_cmwcr_io_mode(dnode_id stat_id, uint16_t config_val){
  write_cmtw_reg(stat_id, CMTW_CMWIOR_OFFSET, config_val);
}

uint32_t cmtw_get_count(dnode_id stat_id){
  return DEV_REW(((cmtw_dstat*) GET_DEV_STAT(stat_id))->baddr, CMTW_CMWCNT_OFFSET);
}

void cmtw_init(dnode_id stat_id){
  cmtw_dstat *cmtw_stat = (cmtw_dstat*)GET_DEV_STAT(stat_id);
  DEV_WRH(cmtw_stat->baddr, CMTW_CMWCR_OFFSET, 0);
  DEV_WRH(cmtw_stat->baddr, CMTW_CMWIOR_OFFSET, 0);
}
