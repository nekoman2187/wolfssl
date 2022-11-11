/*
 * TOPPERS/ASP Kernel
 *     Toyohashi Open Platform for Embedded Real-Time Systems/
 *     Advanced Standard Profile Kernel
 * 
 * Copyright (C) 2016- by Hisashi Hata, JAPAN
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


 /* Target SD RAM : MT48LC16M16A2
  *    speed grade: -7E
  *    Row addressing : 8K A[12:0]
  *    tRP : 15 ns(min)
  *    tRFC : 66 ns(min)
  *    tWR : 1 CLK + 7ns
  *    tRAS : 37 ns
  *    tRCD : 15 ns
  *    tREF : 64 ms
  *    tREF/Row addressing : 7.8125usec
  */


 /* bord setting
  *   SDRAM clock : 60MHz , Tsd=16.66ns
  */

#include "kernel_impl.h"
#include <sil.h>
#include "target_board.h"

#if defined(USE_SYSTEM_SDRAM) || defined(USE_DATA_SDRAM)

#define SDCLK_OUT_WAIT_COUNT 100000 //100 usec

/*
 * Caution:
 *    Following function is called before initializeing of .bss and .data section.
 *    Don't use gloval and static variable.
 */

void 
target_sdram_config( void ){
  volatile uint32_t wait_count;
  
  //disable write protect
  sil_wrh_mem((uint16_t *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC0 | SYSTEM_PRC1);
  //stop output of sdclk and bclk.
  sil_wrw_mem((uint32_t*)CKG_SCKCR_ADDR, sil_rew_mem((uint32_t*)CKG_SCKCR_ADDR) | CKG_SCKCR_PSTOP0 | CKG_SCKCR_PSTOP1);
  //disable buss error moniter
  sil_wrb_mem((uint8_t*)BUS_BEREN_ADDR, BUS_BEREN_IGAEN_DIS | BUS_BEREN_TOEN_DIS);
  //init bus prioryty register
  sil_wrh_mem((uint16_t*)BUS_BUSPRI_ADDR,
              BUS_BUSPRI_BPRA_CONST |
              BUS_BUSPRI_BPRO_CONST |
              BUS_BUSPRI_BPIB_CONST | 
              BUS_BUSPRI_BPGB_CONST |          
              BUS_BUSPRI_BPHB_CONST |
              BUS_BUSPRI_BPFB_CONST |
              BUS_BUSPRI_BPEB_CONST
              );
  //SDRAM multi function Pin config
  sil_wrb_mem((uint8_t*)MPC_PFBCR0_ADDR,
              MPC_PFBCR0_ADRLE_PA07_BUS |
              MPC_PFBCR0_ADRHMS_P9_SEL  |
              MPC_PFBCR0_DHE_BUS |
              MPC_PFBCR0_DH32E_IO |
              MPC_PFBCR0_WR1BC1E_IO |
              MPC_PFBCR0_WR32BC32E_IO
              );
  
  sil_wrb_mem((uint8_t*)MPC_PFBCR1_ADDR,
              MPC_PFBCR1_WATIS_INVALID |
              MPC_PFBCR1_ALEOE_DIS |
              MPC_PFBCR1_MDSDE_EN |
              MPC_PFBCR1_DQM1E_EN |
              MPC_PFBCR1_SDCLKE_EN
              );

  sil_wrb_mem((uint8_t*)MPC_PFAOE0_ADDR,
              MPC_PFAOE0_A8E_EN |
              MPC_PFAOE0_A9E_EN |
              MPC_PFAOE0_A10E_EN |
              MPC_PFAOE0_A11E_EN |
              MPC_PFAOE0_A12E_EN |
              MPC_PFAOE0_A13E_EN |
              MPC_PFAOE0_A14E_EN
              );
  
  sil_wrb_mem((uint8_t*)MPC_PFAOE1_ADDR, 0x0);

  //SDRAM IO PORT config
  sil_wrb_mem((uint8_t*)PORTA_PDR_ADDR, 0x0); //Port A input (AD0-7)
  sil_wrb_mem((uint8_t*)PORTB_PDR_ADDR, 0x0); //Port B input (AD 8-15)
  sil_wrb_mem((uint8_t*)PORT9_PDR_ADDR, 0x0); //Port 9 input (AD16-23)
  sil_wrb_mem((uint8_t*)PORTD_PDR_ADDR, 0x0); //Port E input (D0-7)
  sil_wrb_mem((uint8_t*)PORTE_PDR_ADDR, 0x0); //Port E input (D8-15)
  sil_wrb_mem((uint8_t*)PORT6_PDR_ADDR, 0x0); //Port 6 input SDCS#, RAS#,CAS#, WE#, CKE, DQM0, DQM1
  sil_wrb_mem((uint8_t*)PORT7_PDR_ADDR, sil_reb_mem((uint8_t*)PORT7_PDR_ADDR) & ~PORT_PDR_B0_BIT); //Port 7 input SDCLK

  //system control register
  //ROM, External bus setting
  sil_wrh_mem((uint16_t*)SYSTEM_SYSCR0_ADDR,
              SYSTEM_SYSCR0_KEY |
              SYSTEM_SYSCR0_ROME_EN |
              SYSTEM_SYSCR0_EXBE_EN
              );

  while((sil_reh_mem((uint16_t*)SYSTEM_SYSCR0_ADDR) & SYSTEM_SYSCR0_EXBE_EN) == 0);
  //enable sdclk and bclk.
  sil_wrw_mem((uint32_t*)CKG_SCKCR_ADDR, sil_rew_mem((uint32_t*)CKG_SCKCR_ADDR) & ~(CKG_SCKCR_PSTOP0 | CKG_SCKCR_PSTOP1));
  //Enable write protection
  sil_wrh_mem((uint8_t *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
  
  //wait for 100us over
  for(wait_count=0; wait_count<USEC_TO_COUNT(F_PCLKA, SDCLK_OUT_WAIT_COUNT); wait_count++);
  //SDRAM Initialize Register
  sil_wrh_mem((uint16_t *)BUS_SDIR_ADDR,
              BUS_SDIR_ARFI_4 |  //over tRFC(66ns) Tsd * 4
              BUS_SDIR_ARFC_2 |  //count of init autorefresh
              BUS_SDIR_PRC_3     //over tRP(16 ns) Tsd*3 can't set lower 3
              );
  //SDRAM Initialize sequence control register
  //  initialize sequence start
  sil_wrb_mem((uint8_t*)BUS_SDICR_ADDR, BUS_SDICR_INIRQ_START);
  //waite end of initilize sequence 
  while(sil_reb_mem(BUS_SDSR_ADDR) != 0);
  //SDC control Register
  sil_wrb_mem((uint8_t*)BUS_SDCCR_ADDR,
              BUS_SDCCR_EXENB_DIS | //disable sd controller
              BUS_SDCCR_BSIZE_16 //bus width is 16 bit
              );
  //SD RAM Mode Register
  /* b15    Reserved - The write value should be 0.
    b14:b0 MR[14:0] - Mode Register Setting - Writing to these bits: Mode register set command is issued
                      Mode register definition for MT48LC8M16A2
                        A11:A10  Reserved - The write value should be 0.
                        A9       Write Burst Mode - Single Location Access
                        A8:A7    Operating Mode - Standard Operation
                        A6:A4    CAS Latency - 2
                        A3       Burst Type - Sequential
                        A2:A0    Burst Length - 1 */
  sil_wrh_mem((uint16_t*)BUS_SDMOD_ADDR, 0x0220);
  //SD RAM Timming register
  sil_wrw_mem((uint32_t*)BUS_SDTR_ADDR,
              BUS_SDTR_CL_2 |  //SDTR_RAS lower than SDTR_RCD+SDTR_CL. SDTR_CL have to be same as SDMOD CAS Latency
              BUS_SDTR_WR_2 |  //over tWR(1 CLK+7ns)
              BUS_SDTR_RP_1 |  //over tRP(15ns) Tsd*2
              BUS_SDTR_RCD_1 | //over tRCD(15ns) Tsd*2
              BUS_SDTR_RAS_3  //over tRAS(37ns) Tsd*3
              );
  //SDRAM Address regiset
  sil_wrb_mem((uint8_t*)BUS_SDADR_ADDR, BUS_SDADR_MXC_9); //shift 9bit
  //SDC Mode Register
  sil_wrb_mem((uint8_t*)BUS_SDCMOD_ADDR, BUS_SDCMOD_EMODE_SAME); //Endian mode is same as CPU
  //SDRAM Access mode register
  sil_wrb_mem((uint8_t*)BUS_SDAMOD_ADDR, BUS_SDAMOD_BE_DIS); //Disable burst
  //SDRAM refresh control register
  sil_wrh_mem((uint16_t*)BUS_SDRFCR_ADDR,
              BUS_SDRFCR_REFW_4 | //over tRFC(66ns) Tsd*4
              468  // under 7.8125usec Tsd*468
              ); //
  //SDRAM Auto-Refresh control register
  sil_wrb_mem((uint8_t*)BUS_SDRFEN_ADDR, BUS_SDRFEN_RFEN_EN); //enable auto refresh
  //SDC control Register
  sil_wrb_mem((uint8_t*)BUS_SDCCR_ADDR,
              BUS_SDCCR_EXENB_EN | //enable sd controller
              BUS_SDCCR_BSIZE_16 //bus width is 16 bit
              );
}

#endif
