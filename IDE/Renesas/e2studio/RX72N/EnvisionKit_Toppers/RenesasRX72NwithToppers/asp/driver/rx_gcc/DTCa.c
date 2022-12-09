/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <kernel_impl.h>
#include <driver/rx_gcc/DTCa.h>

//DTC register define
//#define DID_DTCA     //defined in target_device_id.h
#define DTC_DTCCR (DTCA_BASE_ADDR+0x0)
#define DTC_DTCVBR (DTCA_BASE_ADDR+0x4)
#define DTC_DTCADMOD (DTCA_BASE_ADDR+0x8)
#define DTC_DTCST (DTCA_BASE_ADDR+0xC)
#define DTC_DTCSTS (DTCA_BASE_ADDR+0xE)

extern dtca_descriptor *dtca_vect[];

void set_vecter_table(uint8_t intno, dtca_descriptor *vecter){
  dtca_vect[intno] = vecter;
}

//
// DTCA Macro Controll
//
#define DTCA_MODE_ENABLE 0x1
#define DTCA_MODE_DISABLE 0x0

void dtca_enable(){
  sil_wrb_mem((uint8_t*)DTC_DTCST, DTCA_MODE_ENABLE);
  while(sil_reb_mem((uint8_t*)DTC_DTCST) == DTCA_MODE_DISABLE);
}

void dtca_disable(){
  sil_wrb_mem((uint8_t*)DTC_DTCST, DTCA_MODE_DISABLE);
}

//Set DTCER to accept irq.
void dtcer_irq_enable(uint8_t intno){
  ENABLE_ICU_DTCER(intno);
}

void dtcer_irq_disable(uint8_t intno){
  DISABLE_ICU_DTCER(intno);
}

//Deccriptor control

#define ENTRY_HALF_MASK 0xFFFF
#define DESC_MAX_ENTRY 32
#define DESC_ENTRY_HALF (DESC_MAX_ENTRY >> 1)

static uint32_t reserved_desc_entry;
extern dtca_descriptor dtca_desc_table[NUM_DTCA_DESC];

uint8_t desc_bit2id(uint32_t desc_entry_flg){
  uint32_t current_mask, current_flg;
  uint8_t que_id, current_offset;

  que_id =0;
  current_offset = DESC_ENTRY_HALF;
  current_mask = ENTRY_HALF_MASK;
  current_flg = desc_entry_flg;

  if(!desc_entry_flg)
    return 0;

  while(current_offset){
    if(!(current_flg & current_mask)){
      que_id+= current_offset;
      current_flg = current_flg >> current_offset;
    }
    current_offset = current_offset >> 1;
    current_mask = current_mask >> current_offset;
  }
  return que_id+1;
}

static inline uint32_t assign_buff(uint8_t len){
  uint8_t i;
  uint32_t free_entry, seq_free_entry;
  i=1;
  seq_free_entry = free_entry = ~reserved_desc_entry;
  while(i != len){
    seq_free_entry &= (free_entry << i);
    i++;
  }

  seq_free_entry &= (~seq_free_entry+1);
  return seq_free_entry >> (len-1);
}

int8_t dtca_get_desc_buff(desc_buff* dbuff, uint8_t len){
  uint8_t que_id, i;
  uint32_t assigned_entry;

  if(!(assigned_entry = assign_buff(len))){
    dbuff->desc = 0;
    return DESC_ER;
  }

  que_id = desc_bit2id(assigned_entry);

  dbuff->buff_entry = 0;
  for(i=0; i<len; i++){
    dbuff->buff_entry |= (assigned_entry << i);
  }
  reserved_desc_entry |= dbuff->buff_entry;

  dbuff->desc = &dtca_desc_table[que_id-1];
  return DESC_OK;
}

int8_t dtca_rel_desc_buff(desc_buff* dbuff){
  reserved_desc_entry &= (~dbuff->buff_entry);
}

void dtca_init(){
  //init descriptor entry
  reserved_desc_entry = 0;

  //init descriptor base address
  sil_wrw_lem((uint32_t *)DTC_DTCVBR, (uint32_t)dtca_vect);
}

