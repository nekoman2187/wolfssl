/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <kernel_cfg.h>
#include <kernel_impl.h>
#include <target_device/target_device.h>

#ifdef USE_EPTPC_0
#include <driver/rx_gcc/EPTPC.h>

extern uint8_t mac_addr[6];

PTPSYS ptp_sys ={
  EPTPC_STCSELR_SCLKDIV_DIV6|EPTPC_STCSELR_SCLKSEL_PCLKA_DIV_1_6,
  EPTPC_STCFR_STCF_20M
};

extern PTP_PORT ptp_port_conf;

PTPINI ptp_conf ={
  &ptp_sys,
  &ptp_port_conf
};
    
dev_node_t eptpc_node_0 = {
  NULL,
  (void*) &ptp_conf
};


void target_dev_ini_eptpc_0(){

}

#endif
