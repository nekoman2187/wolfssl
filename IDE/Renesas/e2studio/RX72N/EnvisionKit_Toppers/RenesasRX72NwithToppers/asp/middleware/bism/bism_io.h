/*
 bism.c
 Copyright (c) 2016 Hisashi Hata

 This software is released under the MIT License.
 http://opensource.org/licenses/mit-license.php
*/

#ifndef BUILD_IN_SELF_MONITOR_H
#define BUILD_IN_SELF_MONITOR_H
#include <driver/rx_gcc/EPTPC.h>
#include <middleware/include/ff.h>


#define BISM_RTASK_PRIORITY 6
#define	BISM_RTASK_STACK_SIZE 512


FRESULT bism_io_init(uint8_t *log_file);
void bism_io_close();
uint32_t bism_buff_write(uint8_t* w_dat, uint8_t len);
void bism_push_block();
void bism_log_store_task(intptr_t exif);
uint8_t bism_wait_que();

#endif
