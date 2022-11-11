#ifndef ELF_HEAD_ANA_H
#define ELF_HEAD_ANA_H

#include <kernel.h>

#define EI_NIDENT 16

typedef struct rx_elf32_ehdr_t
{
    uint8_t    e_ident[ EI_NIDENT ];
    uint16_t   e_type;
    uint16_t   e_machine;
    uint32_t   e_version;
    uint32_t   e_entry;
    uint32_t   e_phoff;
    uint32_t   e_shoff;
    uint32_t   e_flags;
    uint16_t   e_ehsize;
    uint16_t   e_phentsize;
    uint16_t   e_phnum;
    uint16_t   e_shentsize;
    uint16_t   e_shnum;
    uint16_t   e_shstrndx;
}rx_elf32_ehdr;

typedef struct rx_elf32_phdr_t
{
    uint32_t    p_type;
    uint32_t    p_offset;
    uint32_t    p_vaddr;
    uint32_t    p_paddr;
    uint32_t    p_filesz;
    uint32_t    p_memsz;
    uint32_t    p_flags;
    uint32_t    p_align;
} rx_elf32_phdr;

#endif
