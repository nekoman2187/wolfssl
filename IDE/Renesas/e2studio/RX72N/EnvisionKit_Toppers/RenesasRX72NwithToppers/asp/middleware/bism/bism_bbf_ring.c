/*
 bism_bbf_ring.c
 Copyright (c) 2016 Hisashi Hata

 This software is released under the MIT License.
 http://opensource.org/licenses/mit-license.php
*/

#include <string.h>
#include "bism_bbf_ring.h"

static void bism_blk_buff_init(bism_blk_buff* p_bblk){
  p_bblk->state =  BISM_BUF_IDLE;
  p_bblk->write_pos = 0;
  return;
}

void bism_bbf_ring_init(bism_bbf_ring *bbf_ring){
  bism_blk_buff *bblk;

  bbf_ring->write_buf = bbf_ring->q_buff;
  for(bblk=bbf_ring->q_buff; bblk != &(bbf_ring->q_buff[BISM_BUFFER_COUNT]); bblk++){
    bism_blk_buff_init(bblk);
  }
  bbf_ring->write_num = 0;
  bbf_ring->read_num = 0;
  return;
}

bism_blk_buff* bism_bbf_get_blk(bism_bbf_ring* bbf_ring, uint8_t *buff_st){
  bism_blk_buff * blk_pbuff;
  uint16_t next_read;

  blk_pbuff = &bbf_ring->q_buff[bbf_ring->read_num];
  *buff_st = BBF_LOCK_BLK_NON;
  if(blk_pbuff->state & (BISM_BUF_WLOCK)){
    bism_blk_set_state(blk_pbuff, BISM_BUF_READING);
    next_read = bbf_ring->read_num+1;
    if(next_read >= BISM_BUFFER_COUNT)
      next_read = 0;
    bbf_ring->read_num = next_read;
    //check lock block has
    if(next_read != bbf_ring->write_num)
      *buff_st = BBF_LOCK_BLK_HAS;

    return blk_pbuff;
  }
  return NULL;
}

static bism_blk_buff * bism_bbf_next(bism_bbf_ring* bbf_ring){
  bism_blk_buff *next_buf;
  uint16_t next_num;

  next_num = bbf_ring->write_num + 1;
  if(next_num >= BISM_BUFFER_COUNT)
    next_num = 0;

  next_buf = &bbf_ring->q_buff[next_num];
  if(next_buf->state & (BISM_BUF_IDLE| BISM_BUF_READEND)){
    bbf_ring->write_num = next_num;
    bbf_ring->write_buf = next_buf;
    bism_blk_set_state(next_buf, BISM_BUF_IDLE);
    return next_buf;
  }
  return NULL;
}

int32_t bism_bbf_write(uint8_t* w_data, uint32_t len, uint8_t *buff_st, bism_bbf_ring *bbf_ring){
  bism_blk_buff* c_buff;
  uint32_t rest, cpy_pos, cpy_len;

  *buff_st = BBF_WRITE_OK;
  c_buff = bbf_ring->write_buf;

  //check current buffer block is full
  if(c_buff->state & (BISM_BUF_WLOCK | BISM_BUF_READING | BISM_BUF_READEND)){
    //buffer block full case
    if(!(c_buff = bism_bbf_next(bbf_ring))){
      //can't switch buffer
      *buff_st = BBF_OVER_FLOW;
      return 0;
    }
  }//end current buffer full case

  rest = len;
  cpy_pos = 0;

  while((c_buff->write_pos + rest) >= BISM_BUFFER_SIZE){
    //write data is bigger than rest of buffer
    *buff_st = BBF_LOCK_BLK_HAS;
    cpy_len = BISM_BUFFER_SIZE - c_buff->write_pos;
    //copy data and update statetus for block buffer
    if(cpy_len)
      memcpy(c_buff->buff+c_buff->write_pos, w_data+cpy_pos, cpy_len);

    c_buff->write_pos = BISM_BUFFER_SIZE;
    bism_blk_set_state(c_buff, BISM_BUF_WLOCK);
    //update buffer ring status
    //  swtich block buffer and load current block.
    if(!(c_buff = bism_bbf_next(bbf_ring)))
      return cpy_len;

    rest -= cpy_len;
    cpy_pos += cpy_len;
  }

  if(rest){
    memcpy(c_buff->buff+c_buff->write_pos, w_data+cpy_pos, rest);
    c_buff->write_pos+=rest;
    if(c_buff->state & BISM_BUF_IDLE)
      bism_blk_set_state(c_buff, BISM_BUF_WRITING);
  }
  return len;
}

uint32_t bism_bbf_lock_current(bism_bbf_ring* bbf_ring){
  bism_blk_buff* c_buff;
  c_buff = bbf_ring->write_buf;
  if(c_buff->state & BISM_BUF_WRITING){
    bism_blk_set_state(c_buff, BISM_BUF_WLOCK);
    bism_bbf_next(bbf_ring);
    return BBF_LOCK_BLK_HAS;
  }
  else
    return  BBF_LOCK_BLK_NON;


}
