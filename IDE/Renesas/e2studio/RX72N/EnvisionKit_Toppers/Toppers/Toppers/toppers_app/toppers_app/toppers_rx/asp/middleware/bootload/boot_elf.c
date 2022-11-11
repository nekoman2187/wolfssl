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
#include <string.h>
#include "boot_elf.h"
#include "elf_fio.h"
#include "tinet_target_config.h"

#define SEG_COPY_BUFF_SZ 512
static uint8_t scopy_buff[SEG_COPY_BUFF_SZ];

static void call_startup(rx_elf32_ehdr* ehdr){
  uint32_t entry;
  entry = ehdr->e_entry;
  __asm__("jmp %0": :"r"(entry));
}


int32_t elf32_cpy_seg(rx_elf32_phdr *phdr, FIL* efp){
  uint32_t dist_addr, rest, req_size, readed_size;
  rest = phdr->p_filesz;
  //Check file size
  //When file size is 0, segment is .bss section. do noting.
  if(rest == 0)
    return 0;

  dist_addr = phdr->p_vaddr;

  f_lseek(efp, phdr->p_offset);
  while(rest != 0){
    req_size = (rest > SEG_COPY_BUFF_SZ) ? SEG_COPY_BUFF_SZ : rest;
    if(f_read(efp, scopy_buff, req_size, &readed_size) != FR_OK)
      return -1;
    memcpy((void*)dist_addr, scopy_buff, readed_size);
    //    printf("copy: dist = %x, size = %d, copy = %d\n", dist_addr, readed_size, phdr->p_filesz-rest+readed_size);
    rest -= readed_size;
    dist_addr += readed_size;
  }
  return 0;
}

#define LOAD_PHDR_NUM 8
int deploy_elf(int8_t *elf_fname, rx_elf32_ehdr *ehdr){
  rx_elf32_phdr phdr[LOAD_PHDR_NUM];
  uint32_t phdr_index, hr_len,i;
  FIL efp;

  if(f_open(&efp, elf_fname, FA_READ)!=FR_OK)
    return -1;
  read_ehdr(ehdr, &efp);
  phdr_index = 0;
  while(phdr_index < ehdr->e_phnum){
    hr_len = read_phdr(ehdr, phdr, phdr_index, LOAD_PHDR_NUM, &efp);
    phdr_index += hr_len;
    for(i=0; i<hr_len; i++){
      //      printf("copy phdr: index = %d, size = %d\n", i, phdr[i].p_filesz);
      if(elf32_cpy_seg(&phdr[i], &efp) < 0)
        return -1;
    }
  }
  f_close(&efp);
  return 0;
}

void boot_elf(int8_t *elf_name){
  rx_elf32_ehdr ehdr;
  deploy_elf(elf_name, &ehdr);
  edmac_user_stop();
  set_init_moudlestop_setting();
  call_startup(&ehdr);
}
