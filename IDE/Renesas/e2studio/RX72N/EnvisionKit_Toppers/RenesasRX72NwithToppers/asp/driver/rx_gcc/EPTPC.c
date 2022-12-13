/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2017- by Hisashi Hata, JAPAN
 *
 * The above copyright holders grant permission gratis to use,
 * duplicate, modify, or redistribute (hereafter called use) this
 * software (including the one made by modifying this software),
 * provided that the following four conditions (1) through (4) are
 * satisfied.
 *
 * (1) When this software is used in the form of source code, the above
 *     copyright notice, this use conditions, and the disclaimer shown
 *     below must be retained in the source code without modification.
 *
 * (2) When this software is redistributed in the forms usable for the
 *     development of other software, such as in library form, the above
 *     copyright notice, this use conditions, and the disclaimer shown
 *     below must be shown without modification in the document provided
 *     with the redistributed software, such as the user manual.
 *
 * (3) When this software is redistributed in the forms unusable for the
 *     development of other software, such as the case when the software
 *     is embedded in a piece of equipment, either of the following two
 *     conditions must be satisfied:
 *
 *   (a) The above copyright notice, this use conditions, and the
 *       disclaimer shown below must be shown without modification in
 *       the document provided with the redistributed software, such as
 *     the user manual.
 *
 *   (b) How the software is to be redistributed must be reported to the
 *       TOPPERS Project according to the procedure described
 *       separately.
 *
 * (4) The above copyright holders and the TOPPERS Project are exempt
 *     from responsibility for any type of damage directly or indirectly
 *     caused from the use of this software and are indemnified by any
 *     users or end users of this software from any and all causes of
 *     action whatsoever.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 * THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 * TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 * INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */

#include <kernel_impl.h>
#include <driver/rx_gcc/EPTPC.h>

static void init_synfp(PTPINI* pini);

#define EPTPC_RESET 0
#define EPTPC_OPERATION 1

static uint8_t eptpc_state = EPTPC_RESET;
  
uint32_t get_port_base(PTPINI* pini){
  if(pini->port->ptp_mode & EPTPC_MODE_PORT0){
    return EPTPC_PORT0_BASEADDR;
  }
  else{
    return EPTPC_PORT1_BASEADDR;
  }
}

void eptpc_reset(){
  volatile uint32_t i;
  //enable EPTP reset
  sil_wrw_mem((uint32_t*)EPTPC_PTRSTR_ADDR, EPTPC_PTRSTR_RESET);
  //wait more than 64 PCLK cycle */
  for(i=64; i>0; i--);
  //relese reset
  sil_wrw_mem((uint32_t*)EPTPC_PTRSTR_ADDR, 0);
  eptpc_state = EPTPC_RESET;
}

void eptpc_init(PTPINI* pini){
  uint32_t port_mode;
  uint32_t port_base;
  //reset eptpc
  eptpc_reset();

  port_mode = pini->port->ptp_mode;
  port_base = get_port_base(pini);
  //select use port
  if(port_mode & EPTPC_MODE_PORT0){
    //port0 select
    sil_wrw_mem((uint32_t*)EPTPC_STCHSELR_ADDR, 0);
  }
  else if(port_mode & EPTPC_MODE_PORT1){
    //port1 select
    sil_wrw_mem((uint32_t*)EPTPC_STCHSELR_ADDR, EPTPC_STCHSELR_SYSEL);
  }

  //set eptpc intterupt mask. disable all
  sil_wrw_mem((uint32_t*)EPTPC_MIEIPR_ADDR, 0);
  sil_wrw_mem((uint32_t*)EPTPC_STIPR_ADDR, 0);
  sil_wrw_mem((uint32_t*)EPTPC_PRIPR_ADDR, 0);
  sil_wrw_mem((uint32_t*)(EPTPC_SYIPR_OFFSET+port_base), 0);

  init_synfp(pini);

  //set PTP reception filters. support only ordinary e2e clock
  //config port 0
  
  if(port_mode & EPTPC_MODE_P2P){
    ;//P2P mode not support
  }
  else{
    if(port_mode & EPTPC_MODE_MASTER){
      //master port
      sil_wrw_mem((uint32_t*)(EPTPC_SYRFL1R_OFFSET + port_base), 0x00004000);
      sil_wrw_mem((uint32_t*)(EPTPC_SYRFL2R_OFFSET + port_base), 0x00000000);
      sil_wrw_mem((uint32_t*)(EPTPC_SYCONFR_OFFSET + port_base), 0x00000028);
    }
    else{
      //slave port
      sil_wrw_mem((uint32_t*)(EPTPC_SYRFL1R_OFFSET + port_base), 0x00040440);
      sil_wrw_mem((uint32_t*)(EPTPC_SYRFL2R_OFFSET + port_base), 0x00000000);
      sil_wrw_mem((uint32_t*)(EPTPC_SYCONFR_OFFSET + port_base), 0x00000028);
    }
  }


  sil_wrw_mem((uint32_t*)(EPTPC_SYRVLDR_OFFSET+port_base), 0x00000007);

  //set transfer mode
  sil_wrw_mem((uint32_t*)EPTPC_TRNMR_ADDR, 0x0); //stor and forward mode

  //set intterupt
  sil_wrw_mem((uint32_t*)EPTPC_MIESR_ADDR, 0x3F0000);
  sil_wrw_mem((uint32_t*)EPTPC_STSR_ADDR, (EPTPC_STSR_SYNC | EPTPC_STSR_SYNCOUT | EPTPC_STSR_SYNTOUT | EPTPC_STSR_W10D));
  sil_wrw_mem((uint32_t*)EPTPC_PRSR_ADDR, (EPTPC_PRSR_URE1 | EPTPC_PRSR_URE0 | EPTPC_PRSR_MACE |
                               EPTPC_PRSR_OVRE3 | EPTPC_PRSR_OVRE2 | EPTPC_PRSR_OVRE1 |
                                EPTPC_PRSR_OVRE0) );
  sil_wrw_mem((uint32_t*)(EPTPC_SYSR_OFFSET+port_base), 0x00035277);

  
  sil_wrw_mem((uint32_t*)(EPTPC_SYIPR_OFFSET+port_base), 0x0);
  //interrupt disable
  sil_wrw_mem((uint32_t*)EPTPC_MIEIPR_ADDR, 0);
  eptpc_state = EPTPC_OPERATION;
}

static void init_synfp(PTPINI* pini){
  PTP_PORT* pc;
  uint32_t port_base;
  pc = pini->port;

  port_base = get_port_base(pini);

  //config messeage flag
  sil_wrw_mem((uint32_t*)(EPTPC_ANFR_OFFSET + port_base), PTP_CFG_ANNOUNCE_FLAG);
  sil_wrw_mem((uint32_t*)(EPTPC_SYNFR_OFFSET + port_base), PTP_CFG_SYNC_FLAG);
  sil_wrw_mem((uint32_t*)(EPTPC_DYRQFR_OFFSET + port_base), PTP_CFG_DYRQFR_FLAG);
  sil_wrw_mem((uint32_t*)(EPTPC_DYRPFR_OFFSET + port_base), PTP_CFG_DYRPFR_FLAG);
  //set clock id
  //only support EUI48
  sil_wrw_mem((uint32_t*)(EPTPC_SYCIDRU_OFFSET + port_base), pc->self_clkid[0]);
  sil_wrw_mem((uint32_t*)(EPTPC_SYCIDRL_OFFSET + port_base), pc->self_clkid[1]);
  //set port number
  //portnumber shall be 1, 2, ....
  if(pc->ptp_mode & EPTPC_MODE_PORT0)
    sil_wrw_mem((uint32_t*)(EPTPC_SYPNUMR_OFFSET + port_base), 1);
  else
    sil_wrw_mem((uint32_t*)(EPTPC_SYPNUMR_OFFSET + port_base), 2);
  //synfp transmit enable register
  sil_wrw_mem((uint32_t*)(EPTPC_SYTRENR_OFFSET + port_base), 0x0); //disable all
  //set master clock portidentity
  sil_wrw_mem((uint32_t*)(EPTPC_MTCIDU_OFFSET + port_base), pc->master_clkid[0]);
  sil_wrw_mem((uint32_t*)(EPTPC_MTCIDL_OFFSET + port_base), pc->master_clkid[1]);
  sil_wrw_mem((uint32_t*)(EPTPC_MTPID_OFFSET + port_base), pc->master_portnum);
  //config transmission interval
  sil_wrw_mem((uint32_t*)(EPTPC_SYTLIR_OFFSET + port_base), (PTP_CFG_TRANCE_ANNOUNCE_INTERVAL
                                 | (PTP_CFG_TRANCE_SYNC_INTERVAL << 8)
                                 | (PTP_CFG_TRANCE_DREQ_INTERVAL << 16)));
  //set Announce message parameer
  //grandmaster priority
  sil_wrw_mem((uint32_t*)(EPTPC_GMPR_OFFSET + port_base), (PTP_CFG_GM_PRIORITY_2 | (PTP_CFG_GM_PRIORITY_1 << 16))) ;
  //grandmaster clockquality
  sil_wrw_mem((uint32_t*)(EPTPC_GMCQR_OFFSET + port_base), PTP_CFG_GM_CLKQUALITY);
  //grandmaster port id
  sil_wrw_mem((uint32_t*)(EPTPC_GMIDRU_OFFSET + port_base), pc->grand_master_clkid[0]);
  sil_wrw_mem((uint32_t*)(EPTPC_GMIDRL_OFFSET + port_base), pc->grand_master_clkid[1]);

  sil_wrw_mem((uint32_t*)(EPTPC_CUOTSR_OFFSET + port_base), ((CURRENT_UTC_OFFSET << 16) | TIME_SOURCE_INTERNAL_OSCILLATOR));
  sil_wrw_mem((uint32_t*)(EPTPC_SRR_OFFSET + port_base), 0);
  //Set PTP address
  sil_wrw_mem((uint32_t*)(EPTPC_PPMACRU_OFFSET + port_base), AE_PDELAY_MECHANISM_MSG_U);  //
  sil_wrw_mem((uint32_t*)(EPTPC_PPMACRL_OFFSET + port_base), AE_PDELAY_MECHANISM_MSG_L);  //
  sil_wrw_mem((uint32_t*)(EPTPC_PDMACRU_OFFSET + port_base), PDELAY_MECHANISM_MSG_U);  //
  sil_wrw_mem((uint32_t*)(EPTPC_PDMACRL_OFFSET + port_base), PDELAY_MECHANISM_MSG_L);  //
  sil_wrw_mem((uint32_t*)(EPTPC_PETYPER_OFFSET + port_base), PTP_ETHERTYPE );  //
  //set UDP PTP parameter
  sil_wrw_mem((uint32_t*)(EPTPC_PPIPR_OFFSET + port_base), IPV4_PTP_PRIMARY); //ip address setting
  sil_wrw_mem((uint32_t*)(EPTPC_PDIPR_OFFSET + port_base), IPV4_PTP_PDELAY);  //ip address setting
  sil_wrw_mem((uint32_t*)(EPTPC_PETOSR_OFFSET + port_base), UDP_PTP_EVENT_TOS);  //tos setting
  sil_wrw_mem((uint32_t*)(EPTPC_PGTOSR_OFFSET + port_base), UDP_PTP_GENERAL_TOS);
  sil_wrw_mem((uint32_t*)(EPTPC_PPTTLR_OFFSET + port_base), UDP_PTP_PRIMARY_TTL); //ttl setting
  sil_wrw_mem((uint32_t*)(EPTPC_PDTTLR_OFFSET + port_base), UDP_PTP_PDELAY_TTL);
  //filter setting
  sil_wrw_mem((uint32_t*)(EPTPC_FFLTR_OFFSET + port_base), 0); //filter is disable
  //set udp port number
  sil_wrw_mem((uint32_t*)(EPTPC_PEUDPR_OFFSET + port_base), UDP_PTP_EVENT_PORT_NUM);
  sil_wrw_mem((uint32_t*)(EPTPC_PGUDPR_OFFSET + port_base), UDP_PTP_MCAST_PORT_NUM);
  //set asymmetric delay. (have to set 0x0)
  sil_wrw_mem((uint32_t*)(EPTPC_DASYMRU_OFFSET + port_base), 0x0);
  sil_wrw_mem((uint32_t*)(EPTPC_DASYMRL_OFFSET + port_base), 0x0);
  //set timestamp latency
  sil_wrw_mem((uint32_t*)(EPTPC_TSLATR_OFFSET + port_base), ((((uint32_t)pc->inport_delay) << 16)| ((uint32_t)pc->outport_delay)));
  //set SYNFP frame format. This driver support only ehternet type
  sil_wrw_mem((uint32_t*)(EPTPC_SYFORMR_OFFSET + port_base), 0x0);
  //init reception timeout of PTP messages
  sil_wrw_mem((uint32_t*)(EPTPC_RSTOUTR_OFFSET + port_base),  0x200000); //approx 2s
}


ER eptpc_get_clock(PTPCLK *p_clk){
  sil_wrw_mem((uint32_t*)EPTPC_GETINFOR_ADDR, EPTPC_GETINFOR_INFO);
  while(sil_rew_mem((uint32_t*)EPTPC_GETINFOR_ADDR) == EPTPC_GETINFOR_INFO);

  p_clk->nano_sec = sil_rew_mem((uint32_t*)EPTPC_LCCVRL_ADDR);
  p_clk->sec_l = sil_rew_mem((uint32_t*)EPTPC_LCCVRM_ADDR);
  p_clk->sec_h = sil_rew_mem((uint32_t*)EPTPC_LCCVRU_ADDR);
  return E_OK;
}

ER eptpc_set_clock(PTPCLK *p_clk){
  sil_wrw_mem((uint32_t*)EPTPC_LCIVRL_ADDR, p_clk->nano_sec);
  sil_wrw_mem((uint32_t*)EPTPC_LCIVRM_ADDR, p_clk->sec_l);
  sil_wrw_mem((uint32_t*)EPTPC_LCIVRU_ADDR, p_clk->sec_h);
  sil_wrw_mem((uint32_t*)EPTPC_GETINFOR_ADDR, EPTPC_GETINFOR_INFO);
  return E_OK;
}

//implement R_PTP_Stop r_ptp.c 1504
ER set_w10_times(uint32_t w10_time){
  sil_wrw_mem((uint32_t*)EPTPC_LCIVRU_ADDR, (w10_time & (sil_rew_mem((uint32_t*)EPTPC_STMR_ADDR) & EPTPC_STMR_WINT_MASK)));
  return E_OK;
}

ER ptp_sync_start(PTPINI* pini){
  uint32_t port_mode, wait_count;
  uint32_t port_base;

  if(eptpc_state == EPTPC_RESET)
	  return EPTPC_UN_INIT;
  port_base = get_port_base(pini);
  port_mode = pini->port->ptp_mode;

  //set PTP reception filters. support only ordinary e2e clock
  //config port 0
  if(port_mode & EPTPC_MODE_P2P){
    ;//P2P mode not support
  }
  else{ //E2E port
    if(port_mode & EPTPC_MODE_MASTER){
      //master port
      sil_wrw_mem((uint32_t*)(EPTPC_SYTRENR_OFFSET + port_base), 0x00000010);
    }
    else{
      //slave port
      sil_wrw_mem((uint32_t*)(EPTPC_SYTRENR_OFFSET + port_base), 0x00000100);
      wait_count = 0;
      //wait offset count update
      while((sil_rew_mem((uint32_t*)(EPTPC_SYSR_OFFSET+port_base))&EPTPC_SYSR_OFMUD) == 0){
        if(wait_count > 10){
          return 0;
        }
        wait_count++;
        dly_tsk(1000);
      }

    }
  }

  sil_wrw_mem((uint32_t*)(EPTPC_SYRVLDR_OFFSET +port_base), 0x00000007);

  if(port_mode & EPTPC_MODE_SLAVE){
    sil_wrw_mem((uint32_t*)EPTPC_SYNSTARTR_ADDR, EPTPC_SYNSTARTR_STR);
  }

  return EPTPC_OK;
}

void eptpc_target_config(uint8_t* mac_ad, uint32_t ipclk_conf, uint32_t stca_sel, uint32_t port_mode){
  uint32_t mac_half;
  //set mac address
  if(port_mode & EPTPC_MODE_PORT0){
    mac_half = (mac_ad[0] << 16) | (mac_ad[1] << 8) | mac_ad[2];
    sil_wrw_mem((uint32_t*)EPTPC_PRMACRU0_ADDR, mac_half);
    sil_wrw_mem((uint32_t*)EPTPC_SYMACRU0_ADDR, mac_half);
    mac_half = (mac_ad[3] << 16) | (mac_ad[4] << 8) | mac_ad[5];
    sil_wrw_mem((uint32_t*)EPTPC_PRMACRL0_ADDR, mac_half);
    sil_wrw_mem((uint32_t*)EPTPC_SYMACRL0_ADDR, mac_half);
  }
  else{
    mac_half = (mac_ad[0] << 16) | (mac_ad[1] << 8) | mac_ad[2];
    sil_wrw_mem((uint32_t*)EPTPC_PRMACRU1_ADDR, mac_half);
    mac_half = (mac_ad[3] << 16) | (mac_ad[4] << 8) | mac_ad[5];
    sil_wrw_mem((uint32_t*)EPTPC_PRMACRL1_ADDR, mac_half);
  }
  //set ptp port
  if(port_mode & EPTPC_MODE_PORT0)
    sil_wrw_mem((uint32_t*)EPTPC_TRNDISR_ADDR, (EPTPC_TRNDISR_TDIS_ETH0 & sil_rew_mem((uint32_t*)EPTPC_TRNDISR_ADDR)));
  else
    sil_wrw_mem((uint32_t*)EPTPC_TRNDISR_ADDR, (EPTPC_TRNDISR_TDIS_ETH1 & sil_rew_mem((uint32_t*)EPTPC_TRNDISR_ADDR)));
  sil_wrw_mem((uint32_t*)EPTPC_SYNTDARU_ADDR, 0x1);
  sil_wrw_mem((uint32_t*)EPTPC_SYNTDARL_ADDR, 0x1);
  sil_wrw_mem((uint32_t*)EPTPC_SYNTDBRU_ADDR, 0x2);
  sil_wrw_mem((uint32_t*)EPTPC_SYNTDARL_ADDR, 0x0);
  sil_wrw_mem((uint32_t*)EPTPC_SYNTDARU_ADDR, 0x1);
  //clock config
  sil_wrw_mem((uint32_t*)EPTPC_STCSELR_ADDR, ipclk_conf);
  sil_wrw_mem((uint32_t*)EPTPC_STCFR_ADDR, stca_sel);
  if(port_mode & EPTPC_MODE_PORT0){
    if(port_mode & EPTPC_MODE_MASTER){
      //default time of clock TBD
        sil_wrw_mem((uint32_t*)EPTPC_LCIVRU_ADDR, 0);
        sil_wrw_mem((uint32_t*)EPTPC_LCIVRM_ADDR, 0);
        sil_wrw_mem((uint32_t*)EPTPC_LCIVRL_ADDR, 0);
        sil_wrw_mem((uint32_t*)EPTPC_LCIVLDR_ADDR, EPTPC_LCIVLDR_LOAD);
    }
    else
      sil_wrw_mem((uint32_t*)EPTPC_SYNTOR_ADDR, EPTPC_CFG_SYNC_TOUT);
  }
  sil_wrw_mem((uint32_t*)EPTPC_IPTSELR_ADDR, 0);
  sil_wrw_mem((uint32_t*)EPTPC_MITSELR_ADDR, 0);
  sil_wrw_mem((uint32_t*)EPTPC_ELTSELR_ADDR, 0);  

  sil_wrw_mem((uint32_t*)EPTPC_SYNSTARTR_ADDR, 0);

  if(port_mode & EPTPC_MODE_PORT0){
	  sil_wrw_mem((uint32_t*)(EPTPC_SYRVLDR0_ADDR), 0x00000007);
  }
  else{
	  sil_wrw_mem((uint32_t*)(EPTPC_SYRVLDR1_ADDR), 0x00000007);
  }
}

