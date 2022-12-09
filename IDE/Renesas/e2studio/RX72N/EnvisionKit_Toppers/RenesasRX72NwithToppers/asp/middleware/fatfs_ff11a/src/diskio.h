/*-----------------------------------------------------------------------/
/  Low level disk interface modlue include file   (C)ChaN, 2014          /
/-----------------------------------------------------------------------*/

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

  //#define _USE_WRITE	1	/* 1: Enable disk_write function */
  //#define _USE_IOCTL	1	/* 1: Enable disk_ioctl fucntion */

#include "middleware/fatfs_ff11a/src/integer.h"
#include "driver/include/mmc_sdcard.h"

/*---------------------------------------*/
/* Prototypes for disk control functions */


DSTATUS disk_initialize (BYTE pdrv);
DSTATUS disk_status (BYTE pdrv);
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);

#ifdef __cplusplus
}
#endif

#endif
