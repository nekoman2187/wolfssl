/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 *
 *  Copyright (C) 2016- by Hisashi Hata, JAPAN
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


/*
 *	Clock initialize
 */


#include "kernel_impl.h"
#include <sil.h>
#include "target_board.h"

/*
 * Caution:
 *    Following function is called before initializeing of .bss and .data section.
 *    Don't use gloval and static variable.
 */

void
clock_waitcount_config(void){
  //unlock lopwermode register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC1);

  //clock wait count set
  sil_wrb_mem((void *)(SYSTEM_MOSCWTCR_ADDR),SYSTEM_CLKWAIT_HE );

  //lock lopwermode register access
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
}


void
target_clock_config( void ){

  clock_waitcount_config();

  //unlock access of clock setting register
  sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY | SYSTEM_PRC0);
  //AP_RX64M_0A Bord OSC is 24MHz
  //set clock freq(PLL 120MHz, PCKB 60MHz PCKA 120MHz ICK 120MHz)
  //pll set div 2, mul 10
  sil_wrh_mem((void *)(CKG_PLLCR_ADDR), CKG_PLLCR_PLIDIV2 | CKG_PLLCR_STC10_0);
  //set bus clock rate
  sil_wrw_mem((void *)(CKG_SCKCR_ADDR),   CKG_SCKCR_PD_DIV02
                                        | CKG_SCKCR_PC_DIV02
                                        | CKG_SCKCR_PB_DIV02
                                        | CKG_SCKCR_PA_DIV01
                                        | CKG_SCKCR_BCK_DIV02
                                        | CKG_SCKCR_PSTOP0
                                        | CKG_SCKCR_PSTOP1
                                        | CKG_SCKCR_FCK_DIV02
                                        | CKG_SCKCR_ICK_DIV01);

  sil_wrh_mem((void *)(CKG_SCKCR2_ADDR), CKG_SCKCR2_UCK_NOT_USE);

  /*
   * Main clock setting
   */

  //Main clock disable
   sil_wrb_mem((void *)(CKG_MOSCCR_ADDR), CKG_CLOCK_DISABLE);
   //Set drivabilty of Main clock
   //    clock source is OSC, frequency is 24MHz
   sil_wrb_mem((void *)(CKG_MOFCR_ADDR), CKG_MOFCR_MODRV2_U24);
  //Main clock enable
   sil_wrb_mem((void *)(CKG_MOSCCR_ADDR), CKG_CLOCK_ENABLE);
   //Wait Main clock lock
   while(sil_reb_mem((void *)(CKG_MOSCCR_ADDR)) != CKG_CLOCK_ENABLE);

  //pll enable
   sil_wrb_mem((void *)(CKG_PLLCR2_ADDR), CKG_CLOCK_ENABLE);
   while(sil_reb_mem((void *)(CKG_PLLCR2_ADDR)) != CKG_CLOCK_ENABLE);
   //PLL lock wait
   //wait over 10ms, LOCO freq 125Khz, wait count is 125*10 = 1250;
   //switch clock(PLL select)
   sil_wrh_mem((void *)(CKG_SCKCR3_ADDR),   CKG_SCKCR3_CKSEL_PLL);
  //lock access of clock setting register
   sil_wrh_mem((void *)(SYSTEM_PRCR_ADDR), SYSTEM_PRKEY );
}
