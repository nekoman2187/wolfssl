/*
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2016 Hisashi Hata
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <kernel.h>
#include <target_board.h>
#include <middleware/include/ff.h>
#include "shell_command.h"
#include <driver/rx_gcc/EPTPC.h>

//ptp init mode config
PTP_PORT ptp_port_conf = {
  EPTPC_MODE_E2E | EPTPC_MODE_MASTER | EPTPC_MODE_PORT0,
  {0x000102FF,0xFE030405}, //self clk id
  {0x000102FF,0xFE030405}, //master clk id
  {0x000102FF,0xFE030405}, //grand master clk id
  0x0,
  TSLATR_INGP_RMII100_STCA20,
  TSLATR_EGP_RMII100_STCA20
};

//Ethernet mac address 
uint8_t mac_addr[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

//file io device setting
const dnode_id pdrv_to_dev[1] = {
  DEV_MMC_RSPI0 //drive 1 is mmc_rspi
};

FATFS fatfs;

//ptp mode setting

void init_system_tsk(intptr_t exinf){
  PTPINI *ptp_stat;
  //mount filesystem
  if(f_mount(&fatfs, "", 0) != FR_OK)
	  ext_tsk();
  
  shell_set_usr_cmd(usr_cmd);
  //eptpc init
  ptp_stat = (PTPINI*)GET_DEV_STAT(DEV_EPTPC0);
  while(ptp_sync_start(ptp_stat) == EPTPC_UN_INIT){
    dly_tsk(10);
  }
  ext_tsk();
}
