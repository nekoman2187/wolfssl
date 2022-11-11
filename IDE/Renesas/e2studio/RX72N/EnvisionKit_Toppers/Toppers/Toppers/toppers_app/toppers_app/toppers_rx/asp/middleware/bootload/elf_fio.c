/*
 * Copyright (c) 2016- Hisashi Hata
 * Released under the MIT license
 * http://opensource.org/licenses/mit-license.php
 */

#include "elf_fio.h"

void read_ehdr(rx_elf32_ehdr* ehdr, FIL* efp){
  uint32_t readed;
  
  f_lseek(efp, 0);
  f_read(efp, (uint8_t*)ehdr, sizeof(rx_elf32_ehdr), &readed);
}

uint32_t read_phdr(
               rx_elf32_ehdr* ehdr,
               rx_elf32_phdr* phdr,
               uint32_t phdr_index,
               uint32_t rmax_cnt,
               FIL* efp){
  
  uint32_t readed, read_num;

  if((phdr_index + rmax_cnt) > ehdr->e_phnum)
    read_num = ehdr->e_phnum - phdr_index;
  else
    read_num = rmax_cnt;
  //seek phdr address
  f_lseek(efp, ehdr->e_phoff+sizeof(rx_elf32_phdr) * phdr_index);
  f_read(efp, (uint8_t*)phdr, sizeof(rx_elf32_phdr)*read_num, &readed);
  return read_num;
}
