/*
 bism.c
 Copyright (c) 2016 Hisashi Hata

 This software is released under the MIT License.
 http://opensource.org/licenses/mit-license.php
*/
#include <kernel.h>
#include <kernel_cfg.h>
#include "bism_bbf_ring.h"
#include "bism_io.h"

static bism_bbf_ring bism_buff;
static FIL bism_fp;
static int8_t wait_que_count;

#define BISM_FILE_IDLE 0
#define BISM_FILE_OPEN 1

static uint8_t file_state = BISM_FILE_IDLE;

FRESULT bism_io_init(uint8_t* log_file){
  bism_bbf_ring_init(&bism_buff);
  file_state = BISM_FILE_OPEN;
  wait_que_count = 0;
  return f_open(&bism_fp, log_file, FA_WRITE | FA_CREATE_ALWAYS);
}

void bism_io_close(){
  if(file_state == BISM_FILE_IDLE)
    return;
  while(wait_que_count != 0){
    dly_tsk(10);
  }
  f_close(&bism_fp);
  file_state = BISM_FILE_IDLE;
}

uint32_t bism_buff_write(uint8_t* w_dat, uint8_t len){
  uint8_t buff_st;
  uint32_t writed;
  bism_blk_buff *buff_blk;

  writed = bism_bbf_write(w_dat, len, &buff_st, &bism_buff);
  if(buff_st == BBF_LOCK_BLK_HAS){
    buff_blk = bism_bbf_get_blk(&bism_buff, &buff_st);
    if(buff_blk){
      snd_dtq(BISM_STOR_DTQ, (intptr_t*)buff_blk);
      wait_que_count++;
    }
  }
  return writed;
}

void bism_push_block(){
  uint8_t buff_st;
  bism_blk_buff *buff_blk;

  if(bism_bbf_lock_current(&bism_buff) == BBF_LOCK_BLK_HAS){
    buff_blk = bism_bbf_get_blk(&bism_buff, &buff_st);
    snd_dtq(BISM_STOR_DTQ, (intptr_t*)buff_blk);
    wait_que_count++;
  }
}

void bism_log_store_task(intptr_t exif){
  bism_blk_buff *qued_buff;
  uint32_t writed;
  while(1){
    rcv_dtq(BISM_STOR_DTQ, (intptr_t*)&qued_buff);
    f_write(&bism_fp, qued_buff->buff, qued_buff->write_pos, &writed);
    qued_buff->write_pos = 0;
    bism_blk_set_state(qued_buff, BISM_BUF_READEND);
    wait_que_count--;
  }
}

uint8_t bism_wait_que(){
  return wait_que_count;
}
