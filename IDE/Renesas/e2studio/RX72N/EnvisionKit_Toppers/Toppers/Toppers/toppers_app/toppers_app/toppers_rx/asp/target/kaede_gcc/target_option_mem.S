

    .section .option_memory ROMDATA, align=4
    .glb option_mem_table
option_mem_table:
    .word 0xFFFFFFFF            ;0x0012_0040 SPCC disable all protect
    .space 0x4                  ;0x0012_0044-0x0012_0047 reserved
    .word 0xFFFFFFFF            ;0x0012_0048 TMEF Disable TM
    .space 0x4                  ;0x0012_004C-0x0012_004F reserved
    .word 0xFFFFFFFF            ;0x0012_0050 OSIS OCD Serial ID 4-1
    .word 0xFFFFFFFF            ;0x0012_0054 OSIS OCD Serial ID 8-5
    .word 0xFFFFFFFF            ;0x0012_0058 OSIS OCD Serial ID 12-9
    .word 0xFFFFFFFF            ;0x0012_005C OSIS OCD Serial ID 16-13
    .word 0xFFFFFFFF            ;0x0012_0060 TMINF
    .word 0xFFFFFFFF            ;0x0012_0064 MDE Set Little endian
    .word 0xFFFFFFFF            ;0x0012_0068 OFS0 Disable IWDT
    .word 0xFFFFFFFF            ;0x0012_006C OFS1 Disable voltage moniter
    .end
    
    
