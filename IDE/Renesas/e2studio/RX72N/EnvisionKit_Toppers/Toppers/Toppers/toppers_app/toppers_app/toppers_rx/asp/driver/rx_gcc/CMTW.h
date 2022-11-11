/*
 * Copyright (c) 2018- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#ifndef RX_GCC_DRIVER_CMTW_H
#define RX_GCC_DRIVER_CMTW_H

#include <target_board.h>

typedef struct cmtw_dev_status_type{
  uint32_t baddr; //base address
} cmtw_dstat;


#define CMWCR_CKS_DIV8 0x0
#define CMWCR_CKS_DIV32 0x1
#define CMWCR_CKS_DIV128 0x2
#define CMWCR_CKS_DIV512 0x3
#define CMWCR_CMWIE_EN 0x8
#define CMWCR_CMWIE_DIS 0x0
#define CMWCR_IC0IE_EN 0x10
#define CMWCR_IC0IE_DIS 0x0
#define CMWCR_IC1IE_EN 0x20
#define CMWCR_IC1IE_DIS 0x0
#define CMWCR_OC0IE_EN 0x40
#define CMWCR_OC0IE_DIS 0x0
#define CMWCR_OC1IE_EN 0x80
#define CMWCR_OC1IE_DIS 0x0
#define CMWCR_CMS_16BIT 0x200
#define CMWCR_CMS_32BIT 0x0
#define CMWCR_CCLR_CLR_DIS 0x2000
#define CMWCR_CCLR_CMWICR0_INTCLR 0x8000
#define CMWCR_CCLR_CMWICR1_INTCLR 0xA000
#define CMWCR_CCLR_CMWOCR0_COMCLR 0xC000
#define CMWCR_CCLR_CMWOCR1_COMCLR 0xE000


#define CMTW_CMWIOR_IC0_RISE 0x1
#define CMTW_CMWIOR_IC0_FALL 0x2
#define CMTW_CMWIOR_IC0_DUAL 0x3
#define CMTW_CMWIOR_IC1_RISE 0x4
#define CMTW_CMWIOR_IC1_FALL 0x8
#define CMTW_CMWIOR_IC1_DUAL 0xC
#define CMTW_CMWIOR_IC0E_EN 0x10
#define CMTW_CMWIOR_IC0E_DIS 0x0
#define CMTW_CMWIOR_IC1E_EN 0x20
#define CMTW_CMWIOR_IC1E_DIS 0x0
#define CMTW_CMWIOR_OC0_OUT_RETENT 0x0
#define CMTW_CMWIOR_OC0_H_TOGGLE 0x100
#define CMTW_CMWIOR_OC0_L_TOGGLE 0x300
#define CMTW_CMWIOR_OC1_OUT_RETENT 0x0
#define CMTW_CMWIOR_OC1_H_TOGGLE 0x400
#define CMTW_CMWIOR_OC1_L_TOGGLE 0xC00
#define CMTW_CMWIOR_OC0E_EN 0x1000
#define CMTW_CMWIOR_OC0E_DIS 0x0
#define CMTW_CMWIOR_OC1E_EN 0x2000
#define CMTW_CMWIOR_OC1E_DIS 0x0
#define CMTW_CMWIOR_CMWE_EN 0x8000
#define CMTW_CMWIOR_CMWE_DIS 0x0

void cmtw_count_start(dnode_id stat_id);
void cmtw_count_stop(dnode_id stat_id);
void config_cmwcr_count_mode(dnode_id stat_id, uint16_t config_val);
void config_cmwcr_io_mode(dnode_id stat_id, uint16_t config_val);
uint32_t cmtw_get_count(dnode_id stat_id);
void cmtw_init(dnode_id stat_id);;

#endif
