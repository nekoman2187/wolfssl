/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the toppers license
 * https://www.toppers.jp/license.html
 */
#include <target_board.h>

//device info define
#ifdef USE_RSPI_0
#define RSPI_0_TX_INT_NO INT_RSPI0_SPTI0
#define RSPI_0_RX_INT_NO INT_RSPI0_SPRI0
#endif
