#ifndef ELF_FIO_H
#define ELF_FIO_H

#include <kernel.h>
#include <middleware/include/ff.h>
#include "elf_head.h"

void read_ehdr(rx_elf32_ehdr* ehdr, FIL* efp);

uint32_t read_phdr(
               rx_elf32_ehdr* ehdr,
               rx_elf32_phdr* phdr,
               uint32_t phdr_index,
               uint32_t rmax_cnt,
               FIL* efp);
#endif
