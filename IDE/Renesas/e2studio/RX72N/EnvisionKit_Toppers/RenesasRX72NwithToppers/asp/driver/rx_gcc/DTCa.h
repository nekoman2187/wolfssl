/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#ifndef RENESAS_RX_DTCA_DRIVER
#define RENESAS_RX_DTCA_DRIVER

#ifndef DTCA_MACRO_ONLY
#include "target_device/target_device.h"

//DTC discripeter table
typedef struct dtca_discripter_table {
  volatile uint16_t reserv;
  volatile uint8_t mrb;
  volatile uint8_t mra;
  volatile uint32_t sar;
  volatile uint32_t dar;
  volatile uint16_t crb;
  volatile uint16_t cra;
}dtca_descriptor;

typedef struct desc_buff_t{
  dtca_descriptor *desc;
  uint32_t buff_entry;
} desc_buff;

void dtca_init();
void set_vecter_table(uint8_t intno, dtca_descriptor *vecter);
//descriptor buff control
int8_t dtca_get_desc_buff(desc_buff* dbuff, uint8_t len);
int8_t dtca_rel_desc_buff(desc_buff* dbuff);


//
// DTCA Macro Controll
//
void dtca_enable();
void dtca_disable();

//Set DTCER to accept irq.
void dtcer_irq_enable(uint8_t intno);
void dtcer_irq_disable(uint8_t intno);

//Descriptor buff control
#define DESC_OK 0
#define DESC_ER -1

//DTC register define
//#define DID_DTCA     //defined in target_device_id.h
#define DTC_DTCCR (DTCA_BASE_ADDR+0x0)
#define DTC_DTCVBR (DTCA_BASE_ADDR+0x4)
#define DTC_DTCADMOD (DTCA_BASE_ADDR+0x8)
#define DTC_DTCST (DTCA_BASE_ADDR+0xC)
#define DTC_DTCSTS (DTCA_BASE_ADDR+0xE)

//MRA mode bit
#define MRA_SM_CONST_SAR 0x0
#define MRA_SM_INC_SAR 0x8
#define MRA_SM_DEC_SAR 0xC

#define MRA_SZ_BYTE 0x00
#define MRA_SZ_WORD 0x10
#define MRA_SZ_LONG 0x20

#define MRA_MD_NORMAL 0x00
#define MRA_MD_REPEAT 0x40
#define MRA_MD_BLOCK 0x80

//MRB mode bit
#define MRB_DM_CONST_DAR 0x0
#define MRB_DM_INC_DAR 0x8
#define MRB_DM_DEC_DAR 0xC

#define MRB_DTS_SOURCE 0x10
#define MRB_DTS_DIST 0x00

#define MRB_MISEL_END_IRQ_REQ 0x00
#define MRB_MISEL_TRAN_IRQ_REQ 0x20

#define MRB_CHNS_SEQ 0x00
#define MRB_CHNS_CHNG 0x40

#define MRB_CHNE_DIS 0x00
#define MRB_CHNE_EN 0x80

#endif //DTCA_MACRO_ONLY

#define DTCA_DESC_SIZE 16 //seize of dtca_descriptor
#define NUM_DTCA_DESC 8

#endif
