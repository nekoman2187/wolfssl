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
#include "syssvc/syslog.h"

//ptp init mode config
PTP_PORT ptp_port_conf = {
  EPTPC_MODE_E2E | EPTPC_MODE_SLAVE | EPTPC_MODE_PORT0,
  {0x001112FF,0xFE131415}, //self clk id
  {0x000102FF,0xFE030405}, //master clk id
  {0x000102FF,0xFE030405}, //grand master clk id
  0x1,
  TSLATR_INGP_RMII100_STCA20,
  TSLATR_EGP_RMII100_STCA20
};


//Ethernet mac address 
uint8_t mac_addr[6] = {0x00, 0x11, 0x12, 0x13, 0x14, 0x15};

//file io device setting
const dnode_id pdrv_to_dev[1] = {
  DEV_MMC_RSPI0 //drive 1 is mmc_rspi
};

FATFS fatfs;

//ptp mode setting

void init_system_tsk(intptr_t exinf){
  PTPINI *ptp_stat;
  //mount filesystem
  if(f_mount(&fatfs, "", 0) != FR_OK){
      syslog(LOG_NOTICE, "fs mount error");
	  ext_tsk();
  }
  syslog(LOG_NOTICE, "register user cmd");  
  shell_set_usr_cmd(usr_cmd);
  syslog(LOG_NOTICE, "register user cmd end");    
  //eptpc init
  ptp_stat = (PTPINI*)GET_DEV_STAT(DEV_EPTPC0);
  syslog(LOG_NOTICE, "ptp_start");
  while(ptp_sync_start(ptp_stat) == EPTPC_UN_INIT){
    syslog(LOG_NOTICE, "ptp_init wait %x, %x", ptp_port_conf.ptp_mode, (uint32_t)&ptp_port_conf );    
    dly_tsk(100);
  }
 syslog(LOG_NOTICE, "ptp_init end");      
  ext_tsk();
}
