/*
 bism_fifo.h
 Copyright (c) 2016 Hisashi Hata

 This software is released under the MIT License.
 http://opensource.org/licenses/mit-license.php
*/

#ifndef BISM_FIFO_H
#define BISM_FIFO_H

#include <kernel.h>


#define BISM_BUFFER_SIZE 512
#define BISM_BUFFER_COUNT 2

#define BISM_BUF_IDLE 0x1
#define BISM_BUF_WRITING 0x2
#define BISM_BUF_WLOCK 0x4
#define BISM_BUF_RREDY 0x20
#define BISM_BUF_READING 0x40
#define BISM_BUF_READEND 0x80

//define buffer satatus
#define BBF_WRITE_OK 0x0
#define BBF_LOCK_BLK_NON 0x1
#define BBF_LOCK_BLK_HAS 0x2
#define BBF_OVER_FLOW 0x3

typedef struct bism_block_buffer{
  uint32_t state;
  uint8_t buff[BISM_BUFFER_SIZE];
  uint16_t write_pos;
  uint16_t read_pos;
}bism_blk_buff;

#define bism_blk_set_state(b_buff, set_st) (b_buff->state = set_st)

typedef struct bism_blk_buff_ring{
  bism_blk_buff *write_buf;
  bism_blk_buff q_buff[BISM_BUFFER_COUNT];
  uint16_t write_num;  //number of write buffer(current_buffer)
  uint16_t read_num; //number of read buff
}bism_bbf_ring;

void bism_bbf_ring_init(bism_bbf_ring *bbf_ring);
bism_blk_buff* bism_bbf_get_blk(bism_bbf_ring* bbf_ring, uint8_t *buff_st);
int32_t bism_bbf_write(uint8_t* w_data, uint32_t len, uint8_t *buff_st, bism_bbf_ring *bbf_ring);
uint32_t bism_bbf_lock_current(bism_bbf_ring* bbf_ring);

#endif //BISM_FIFO_H
