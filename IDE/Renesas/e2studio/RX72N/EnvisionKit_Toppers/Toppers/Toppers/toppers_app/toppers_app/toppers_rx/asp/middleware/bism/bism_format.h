/********************************************************
 *                                                      *
 * Copyright (c) 2015- Hisashi Hata                     *
 * Released under the MIT license                       *
 * http://opensource.org/licenses/mit-license.php       *
 *                                                      *
 ********************************************************/
#ifndef _BISM_H_DEFINE
#define _BISM_H_DEFINE

#ifdef _USE_BISM_LARGEFILE
//#define _LARGEFILE_SOURCE
//#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#endif

#ifndef _USE_BISM_LARGEFILE
#define fseeko fseek
#define ftello ftell
#define off_t int32_t
#endif

#define HEADER_TYPE 0x80
#define T1_HEADER_LEN 1
#define T2_HEADER_LEN 2
#define TIMER_SIZE_STEP 4
#define TIMER_32BIT_LEN 4
#define TIMER_64BIT_LEN 8
#define TIMER_MAX_LEN 8
//1 byte header log define
#define T1_TIMER_LEN_MASK 0x40
#define T1_TIMER_LEN_FLG 0x40

#define T1_EVENT_CLASS_MASK 0x20
#define T1_EVENT_CLASS_FLG 0x20
#define T1_EVENT_CLASS_LEN_0 1
#define T1_EVENT_CLASS_LEN_1 2
#define T1_EVENT_CLASS_SHIFT 5
#define T1_EVENT_LEN_MASK 0x10
#define T1_EVENT_LEN_FLG 0x10
#define T1_EVENT_LEN_FLG 0x10
#define T1_EVENT_LEN_0 2
#define T1_EVENT_LEN_1 4
#define T1_EVENT_SHIFT 4
#define T1_USER_DATA_MAX_LEN 24
#define T1_USER_DATA_TYPE_MASK 0x8
#define T1_USER_DATA_MASK 0x7
#define T1_USER_DSTEP 2
#define T1_USER_DOFFSET 8

#endif
