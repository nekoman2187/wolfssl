/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#include <kernel_impl.h>
#include <driver/rx_gcc/RSPI.h>
#include <driver/rx_gcc/DTCa.h>

#define SPCR_OFFSET 0x0
#define SSLP_OFFSET 0x1
#define SPPCR_OFFSET 0x2
#define SPSR_OFFSET 0x3
#define SPDR_OFFSET 0x4
#define SPSCR_OFFSET 0x8
#define SPSSR_OFFSET 0x9
#define SPBR_OFFSET 0xA
#define SPDCR_OFFSET 0xB
#define SPCKD_OFFSET 0xC
#define SSLND_OFFSET 0xD
#define SPND_OFFSET 0xE
#define SPCR2_OFFSET 0xF
#define SPCMD_OFFSET 0x10

//interrupt wait type
#define RSPI_TX_START_WAIT 0x1
#define RSPI_RX_START_WAIT 0x2
#define RSPI_TX_END_WAIT 0x4
#define RSPI_RX_END_WAIT 0x8


void rspi_slave_select(void *v_rspi_stat, uint8_t sel){
  uint8_t st;
  uint32_t base_addr;
  rspi_dstat *rspi_stat;
  rspi_stat = v_rspi_stat;
  
  base_addr = rspi_stat->baddr;
  st = DEV_REB(base_addr, SSLP_OFFSET);
  DEV_WRB(base_addr, SSLP_OFFSET, st & ~sel);
}
  

void rspi_slave_unselect(void *v_rspi_stat, uint8_t unsel){
  uint8_t st;
  uint32_t base_addr;
  rspi_dstat *rspi_stat;
  rspi_stat = v_rspi_stat;
  
  base_addr = rspi_stat->baddr;
  st = DEV_REB(base_addr, SSLP_OFFSET);
  DEV_WRB(base_addr, SSLP_OFFSET, st | unsel);
}

//
//trs_freq is bit rate
//if bit rate is 400 khz, set 400000;
void rspi_init(void *v_rspi_stat, rspi_param_t* params){
  uint32_t base_addr;
  rspi_dstat *rspi_stat;
  rspi_stat = v_rspi_stat;
  
  base_addr = rspi_stat->baddr;
  DEV_WRB(base_addr, SPCR_OFFSET, 0); //disable RSPI
  DEV_WRB(base_addr, SSLP_OFFSET, params->sslp);
  DEV_WRB(base_addr, SPPCR_OFFSET, params->sppcr);
  DEV_WRB(base_addr, SPSCR_OFFSET, params->spscr);
  DEV_WRB(base_addr, SPDCR_OFFSET, params->spdcr);
  DEV_WRH(base_addr, SPCMD_OFFSET, params->spcmd0);  //Set Transfar length 8bit
  DEV_WRB(base_addr, SPBR_OFFSET, (F_PCLKB/2/(params->bit_rate) -1));
  DEV_WRB(base_addr, SPCR_OFFSET, params->spcr); //Enable RSPI 
}

void rspi_disable(void *v_rspi_stat){
  uint32_t base_addr;
  rspi_dstat *rspi_stat;
  uint8_t rd;
  rspi_stat = v_rspi_stat;
  
  base_addr = rspi_stat->baddr;
  rd = DEV_REB(base_addr, SPCR_OFFSET);
  DEV_WRB(base_addr, SPCR_OFFSET, rd & ~SPCR_SPE); //disable RSPI
}
  
void rspi_enable(void *v_rspi_stat){
  uint32_t base_addr;
  uint8_t rd;
  rspi_dstat *rspi_stat;
  rspi_stat = v_rspi_stat;
  
  base_addr = rspi_stat->baddr;
  rd = DEV_REB(base_addr, SPCR_OFFSET);
  DEV_WRB(base_addr, SPCR_OFFSET, rd | SPCR_SPE); //disable RSPI
}

//Bit rate controll register
void rspi_chg_bit_rate(void *v_rspi_stat, uint8_t bit_rate){
  rspi_dstat *rspi_stat;
  rspi_stat = v_rspi_stat;

  DEV_WRB(rspi_stat->baddr, SPBR_OFFSET, bit_rate);
}

//SEND/RECIVE DATA REGISTER
/*
void rspi_dtc_send_w();
void rspi_dtc_send_b();
void rspi_dtc_send_clock();
*/

void rspi_send_w(void *v_rspi_stat, uint32_t dat){
  DEV_WRW(((rspi_dstat*)v_rspi_stat)->baddr, SPDR_OFFSET, dat);
}

void rspi_send_h(void *v_rspi_stat, uint16_t dat){
  DEV_WRW(((rspi_dstat*)v_rspi_stat)->baddr, SPDR_OFFSET, (uint32_t)dat);
}

void rspi_send_b(void *v_rspi_stat, uint8_t dat){
  DEV_WRW(((rspi_dstat*)v_rspi_stat)->baddr, SPDR_OFFSET, (uint32_t)dat);
}

void rspi_send_clock();

void rcv_w_with_dtc();
void rcv_b_with_dtc();

uint32_t rspi_rcv_w(void *v_rspi_stat){
  return DEV_REW(((rspi_dstat*)v_rspi_stat)->baddr, SPDR_OFFSET);
}

uint16_t rspi_rcv_h(void *v_rspi_stat){
  return (uint16_t)DEV_REW(((rspi_dstat*)v_rspi_stat)->baddr, SPDR_OFFSET);
}

uint8_t rspi_rcv_b(void *v_rspi_stat){
  return (uint8_t) DEV_REW(((rspi_dstat*)v_rspi_stat)->baddr, SPDR_OFFSET);
};

inline void rspi_int_sem_init(rspi_dstat *rspi_stat){
  T_RSEM pk_rsem;
  if(ref_sem(rspi_stat->int_sync_sem, &pk_rsem) == E_OK){
	if(pk_rsem.semcnt == 1){
      wai_sem(rspi_stat->int_sync_sem);
    }
  }
}

void rspi_set_spcr_flg_b(uint8_t* baddr, uint8_t set_flg){
  uint8_t st;
  uint8_t *spcr_p;

  spcr_p = baddr + SPCR_OFFSET;
  st = sil_reb_mem(spcr_p);
  sil_wrb_mem(spcr_p, st | set_flg );
}

void rspi_clr_spcr_flg_b(uint8_t* baddr, uint8_t clr_flg){
  uint8_t st;
  uint8_t *spcr_p;

  spcr_p = baddr + SPCR_OFFSET;
  st = sil_reb_mem(spcr_p);
  sil_wrb_mem(spcr_p, (st & ~clr_flg));
}

uint32_t rspi_xchg_rw (void *v_rspi_stat,  uint32_t dat){
  rspi_dstat *rspi_stat;
  uint32_t baddr;
  uint32_t* spdr_addr;

  rspi_stat = (rspi_dstat*)v_rspi_stat;
  baddr = rspi_stat->baddr;
  spdr_addr = (uint32_t*)(baddr + SPDR_OFFSET);
  rspi_int_sem_init(rspi_stat);

  //set rx intterupt wait mode
  rspi_stat->interrupt_wait_flg = RSPI_RX_END_WAIT;
  //enable rx interrupt
  rspi_set_spcr_flg_b((uint8_t*)baddr, SPCR_SPRIE);
  //write data
  sil_wrw_mem(spdr_addr, dat);

  //waint interrupt
  twai_sem(rspi_stat->int_sync_sem, 1000);
  //clear interrupt request
  x_clear_int(rspi_stat->spri);
  //disable rx interrupt
  rspi_clr_spcr_flg_b((uint8_t*)baddr, SPCR_SPRIE);
  return sil_rew_mem(spdr_addr);
}


uint8_t rspi_status(void *v_rspi_stat){
  return DEV_REB(((rspi_dstat*)v_rspi_stat)->baddr, SPSR_OFFSET);
}

void rspi_set_cmd(void *v_rspi_stat, uint8_t cmd_buff_num, uint8_t cmd){
  DEV_WRB(((rspi_dstat*)v_rspi_stat)->baddr, SPCMD_OFFSET+(cmd_buff_num<<1), cmd );
}

void rspi_chg_dwidth(void *v_rspi_stat, uint8_t cmd_buff_num, uint32_t width){
  uint16_t current;
  uint32_t cmd_offset;
  uint32_t base_addr;
  rspi_dstat *rspi_stat;
  rspi_stat = v_rspi_stat;

  cmd_offset = SPCMD_OFFSET+(cmd_buff_num<<1);
  base_addr = rspi_stat->baddr;
  current = DEV_REB(base_addr, cmd_offset);
  DEV_WRH(base_addr, cmd_offset, (current & ~SPCMD_SPB_MASK)|width);
}


void rspi_get_right(void *v_rspi_stat){
  wai_sem(((rspi_dstat*)v_rspi_stat)->ip_lock_sem);
}
  

void rspi_relese_right(void *v_rspi_stat){
  sig_sem(((rspi_dstat*)v_rspi_stat)->ip_lock_sem);
}
  

#include <driver/rx_gcc/DTCa.h>

/*
 * define dtca buffer and table
 */

//tx dummy data
const uint32_t rspi_tx_dummy = 0xffffffff;

/****************************************************
 *  DTCa transfer function                          *
 *    size of transfer data must be aligned 4 byte. *
 *                                                  *
 ****************************************************/
desc_buff dbuff;
dtca_descriptor *tx_dtca_desc;
dtca_descriptor *rx_dtca_desc;

void rspi_recieve_by_dtca(void *v_rspi_stat, uint32_t* s_buff, uint32_t s_size){
  rspi_dstat *rspi_stat;
  uint8_t spdcr_config ;
  uint32_t tx_int_no, rx_int_no, baddr, block_count, i;

  rspi_stat = (rspi_dstat*)v_rspi_stat;
  tx_int_no = rspi_stat->spti;
  rx_int_no = rspi_stat->spri;
  baddr = rspi_stat->baddr;
  block_count = s_size /(4*4); //transfer size/(word_size(4byte) * stack_size(4word))

  rspi_int_sem_init(rspi_stat);
  //set spdcr to 4 flame buffer
  spdcr_config = sil_reb_mem((uint8_t*)(baddr+SPDCR_OFFSET));
  sil_wrb_mem((uint8_t*)(baddr+SPDCR_OFFSET), (spdcr_config & ~SPDCR_SPFC_MASK) | SPDCR_SPFC_4);

  if(block_count != 1){
    dtca_get_desc_buff(&dbuff, 2);
    rx_dtca_desc = dbuff.desc;
    tx_dtca_desc = dbuff.desc+1;

    //set dtca descriptor
    //  blobk transfer mode: block count is 4;

    rx_dtca_desc->mra = MRA_MD_BLOCK | MRA_SZ_LONG | MRA_SM_CONST_SAR;
    //    rx_dtca_desc->mrb = MRB_CHNE_DIS | MRB_DTS_SOURCE | MRB_DM_INC_DAR;
    rx_dtca_desc->mrb = MRB_CHNE_EN | MRB_DTS_SOURCE | MRB_DM_INC_DAR ;    
    rx_dtca_desc->sar = (baddr + SPDR_OFFSET);
    rx_dtca_desc->dar = (uint32_t)s_buff;
    rx_dtca_desc->cra = 0x0404;
    rx_dtca_desc->crb = block_count-1;
    
    tx_dtca_desc->mra = MRA_MD_BLOCK | MRA_SZ_LONG | MRA_SM_CONST_SAR;
    tx_dtca_desc->mrb = MRB_CHNE_DIS | MRB_DTS_DIST | MRB_DM_CONST_DAR;
    tx_dtca_desc->sar = (uint32_t)&rspi_tx_dummy;
    tx_dtca_desc->dar = (baddr + SPDR_OFFSET);
    tx_dtca_desc->cra = 0x0404;
    tx_dtca_desc->crb = block_count-1;
    //disable rspi interface and tx interrupt
    rspi_clr_spcr_flg_b((uint8_t*)baddr, SPCR_SPTIE|SPCR_SPRIE|SPCR_SPE);

    //dtca config
    //    set_vecter_table(tx_int_no, tx_dtca_desc);
    set_vecter_table(rx_int_no, rx_dtca_desc);
    dtcer_irq_enable(tx_int_no);
    dtcer_irq_enable(rx_int_no);
    dtca_enable();
    //set tx intterupt wait mode
    rspi_stat->interrupt_wait_flg = (RSPI_RX_START_WAIT | RSPI_RX_END_WAIT);
    //enable rspi inerface, tx interrupt, rx interrupt
    //  tx interrupt will occur when SPTI and SPE are set same time.
  //rspi_set_spcr_flg_b((uint8_t*)(baddr), SPCR_SPTIE|SPCR_SPRIE|SPCR_SPE);
	rspi_set_spcr_flg_b((uint8_t*)(baddr), SPCR_SPRIE|SPCR_SPE);    

    for(i=0; i<4; i++)
      sil_wrw_mem((uint32_t*)(baddr+SPDR_OFFSET), rspi_tx_dummy);

    //wait rx end
    twai_sem(rspi_stat->int_sync_sem, 1000);
    
    for(i=((block_count-1)*4); i<block_count*4; i++)
      s_buff[i] = sil_rew_mem((uint32_t*)(baddr+SPDR_OFFSET));
    
    //clear interrupt request
    x_clear_int(tx_int_no);
    x_clear_int(rx_int_no);
    
    dtca_rel_desc_buff(&dbuff);
  }
  else{
    rspi_stat->interrupt_wait_flg = RSPI_RX_END_WAIT;
    for(i=0; i<4; i++)
      sil_wrw_mem((uint32_t*)(baddr+SPDR_OFFSET), rspi_tx_dummy);
    rspi_set_spcr_flg_b((uint8_t*)(baddr), SPCR_SPRIE); //enable rx intterupt
    
    twai_sem(rspi_stat->int_sync_sem, 1000);
    x_clear_int(rx_int_no);
    for(i=0; i<4; i++)
      s_buff[i] = sil_rew_mem((uint32_t*)(baddr+SPDR_OFFSET));
  }

  //disable rspi interrupt
  rspi_clr_spcr_flg_b((uint8_t*)baddr, SPCR_SPTIE|SPCR_SPRIE);

  //restore SPDCR
  sil_wrb_mem((uint8_t*)(baddr+SPDCR_OFFSET), spdcr_config);

}


void rspi_send_by_dtca(void *v_rspi_stat, uint32_t* s_buff, uint32_t s_size){
  rspi_dstat *rspi_stat;
  uint8_t spdcr_config ;
  uint32_t tx_int_no, baddr, block_count, i;
  ER check;


  rspi_stat = (rspi_dstat*)v_rspi_stat;
  tx_int_no = rspi_stat->spti;
  baddr = rspi_stat->baddr;
  block_count = s_size /(4*4); //transfer size/(word_size(4byte) * stack_size(4word))

  rspi_int_sem_init(rspi_stat);

  //set spdcr to 4 flame buffer
  spdcr_config = sil_reb_mem((uint8_t*)(baddr+SPDCR_OFFSET));
  sil_wrb_mem((uint8_t*)(baddr+SPDCR_OFFSET), (spdcr_config & ~SPDCR_SPFC_MASK) | SPDCR_SPFC_4);

  if(block_count != 1){
    dtca_get_desc_buff(&dbuff, 1);
    tx_dtca_desc = dbuff.desc;
    //set dtca descriptor
    //  blobk transfer mode: block count is 4;
    tx_dtca_desc->mra = MRA_MD_BLOCK | MRA_SZ_LONG | MRA_SM_INC_SAR;
    tx_dtca_desc->mrb = MRB_CHNE_DIS | MRB_DTS_DIST | MRB_DM_CONST_DAR;
    tx_dtca_desc->sar = (uint32_t)s_buff;
    tx_dtca_desc->dar = (baddr + SPDR_OFFSET);
    tx_dtca_desc->cra = 0x0404;
    tx_dtca_desc->crb = block_count;
  
    //set tx intterupt wait mode
    rspi_stat->interrupt_wait_flg = (RSPI_TX_START_WAIT| RSPI_TX_END_WAIT);
    //disable rspi interface and tx interrupt
    rspi_clr_spcr_flg_b((uint8_t*)baddr, SPCR_SPTIE|SPCR_SPE|SPCR_TXMD);

    //dtca config
    set_vecter_table(tx_int_no, tx_dtca_desc);
    dtcer_irq_enable(tx_int_no);
    dtca_enable();

    //enable rspi inerface and tx interrupt
    //  tx interrupt will occur when SPTI and SPE are set same time.
	rspi_set_spcr_flg_b((uint8_t*)(baddr), SPCR_SPTIE|SPCR_TXMD|SPCR_SPE);
    //waint interrupt
    check = twai_sem(rspi_stat->int_sync_sem, 1000);

    dtca_rel_desc_buff(&dbuff);
  }
  else{
    //set tx intterupt wait mode
    rspi_stat->interrupt_wait_flg |= RSPI_TX_END_WAIT;
    for(i=0; i<4; i++)
      sil_wrw_mem((uint32_t*)(baddr+SPDR_OFFSET), s_buff[i]);
    rspi_set_spcr_flg_b((uint8_t*)(baddr), SPCR_SPTIE|SPCR_TXMD);
    //waint interrupt
    twai_sem(rspi_stat->int_sync_sem, 100000);
  }

  //clear interrupt request
  x_clear_int(tx_int_no);
  //disable rspi tx interrupt
  while (rspi_status(rspi_stat) & SPSR_IDLNF);
  rspi_clr_spcr_flg_b((uint8_t*)baddr, SPCR_SPTIE|SPCR_TXMD);

  //restore SPDCR
  sil_wrb_mem((uint8_t*)(baddr+SPDCR_OFFSET), spdcr_config);

}

void rspi_tx_int_handler(intptr_t exinf){
  rspi_dstat *rspi_stat;
  uint16_t wait_flg;

  rspi_stat = (rspi_dstat*)GET_DEV_STAT((dnode_id) exinf);
  wait_flg = rspi_stat->interrupt_wait_flg;  
  if(wait_flg & RSPI_TX_START_WAIT){
    wait_flg &=  (~RSPI_TX_START_WAIT);
  }else if(wait_flg & RSPI_TX_END_WAIT){
    isig_sem(rspi_stat->int_sync_sem);
  }
  rspi_stat->interrupt_wait_flg = wait_flg;
}

void rspi_rx_int_handler(intptr_t exinf){
  rspi_dstat *rspi_stat;
  uint16_t wait_flg;
  
  rspi_stat = (rspi_dstat*)GET_DEV_STAT((dnode_id) exinf);
  wait_flg = rspi_stat->interrupt_wait_flg;
  
  if(wait_flg & RSPI_RX_START_WAIT){
    wait_flg &=  (~RSPI_RX_START_WAIT);
  }
  else if(wait_flg & RSPI_RX_END_WAIT){
    wait_flg &=  (~RSPI_RX_END_WAIT);
    isig_sem(rspi_stat->int_sync_sem);
  }
  rspi_stat->interrupt_wait_flg = wait_flg;
}


