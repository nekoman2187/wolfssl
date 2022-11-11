/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#ifndef SAURA_GCC_TARGET_DEVICE
#define SAURA_GCC_TARGET_DEVICE

#include <target_device/target_device_id.h>

typedef struct device_node_t{
  void* func;
  void* stat;
}dev_node_t;

typedef struct device_info_t{
  uint32_t status;
  dev_node_t *dnode;
}dev_info_t;

extern dev_info_t dev_info[NUM_TARGET_DEVICE];

#define GET_DEV_NODE(device_id) (dev_info[device_id].dnode)
#define GET_DEV_STAT(device_id) (dev_info[device_id].dnode->stat)
#define GET_DEV_FUNC(device_id) (dev_info[device_id].dnode->func)

void target_device_init();

#define DEV_WRB(base, offset, data) sil_wrb_mem(((uint8_t *)(base+offset)), data)
#define DEV_WRH(base, offset, data) sil_wrh_mem(((uint16_t *)(base+offset)), data)
#define DEV_WRW(base, offset, data) sil_wrw_mem(((uint32_t *)(base+offset)), data)

#define DEV_REB(base, offset) sil_reb_mem((uint8_t*)(base+offset))
#define DEV_REH(base, offset) sil_reh_mem((uint16_t*)(base+offset))
#define DEV_REW(base, offset) sil_rew_mem((uint32_t*)(base+offset))

#endif
