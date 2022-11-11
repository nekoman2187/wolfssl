/*
 * Copyright (c) 2015- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */

#ifndef TARGET_TARGET_DEVICE_ID_H
#define TARGET_TARGET_DEVICE_ID_H

typedef enum use_device_id{
  DEV_NULL,
#ifdef USE_RSPI_0
  DEV_RSPI0,
#endif
#ifdef USE_MMC_RSPI_0
  DEV_MMC_RSPI0,
#endif
#ifdef USE_MMC_GPIO_0
  DEV_MMC_GPIO0,
#endif
#ifdef USE_DTCA_0
  DEV_DTCA0,
#endif
#ifdef USE_SCIG_0
  DEV_SCIG0,
#endif
#ifdef USE_EPTPC_0
  DEV_EPTPC0,
#endif
  NUM_TARGET_DEVICE
}dnode_id;

#endif
