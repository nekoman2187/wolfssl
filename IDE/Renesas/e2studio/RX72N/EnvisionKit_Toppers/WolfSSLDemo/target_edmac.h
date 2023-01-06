/*target_edmac.h
 *
 * Copyright (C) 2006-2022 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

/*
 *		EDMACモジュール（RX72N用）
 *
 */

#ifndef TOPPERS_TARGET_72N_EDMAC_H
#define TOPPERS_TARGET_72N_EDMAC_H
#include <sil.h>
#include "target_board.h"
#include "prc_kernel.h"

//#define INTNO_EDMAC_0	113			/* 割込み番号 */

#define INHNO_EDMAC_0		INT_EDMAC0		/* 割込みハンドラ番号 */
#define INTNO_EDMAC_0		INT_EDMAC0		/* 割込み番号 */
#define INTPRI_EDMAC_0	-5					/* 割込み優先度 */
#define INTATR_EDMAC_0	TA_ENAINT | TA_EDGE	/* 割込み属性 */
#ifndef TOPPERS_MACRO_ONLY

extern void	rx72n_edmac_interrput_wrapper(void);

#endif
#endif /* TOPPERS_TARGET_72N_EDMAC_H */


