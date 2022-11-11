MEMORY
{
    FLASH (rx) : ORIGIN = 0xFFC00000, LENGTH = 4096K
    OPTION_FLASH (rx) : ORIGIN = 0x00120040, LENGTH = 48
    SRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 512K
}

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);
STARTUP(start.o)

SECTIONS
{

	.text :
	{
		__text = .;
		*(.vector)
		*(.text)
		*(.text.*)
		*(P)
	} > FLASH
	_etext = .;
	PROVIDE(etext = .);

	.rodata :
	{
		*(.rodata)
		*(.rodata.*)
		*(C_1)
		*(C_2)
		*(C)
		*(C$VECT)
	} > FLASH
    __rodata_end = .;
	__exidx_start = .;
	__exidx_end = .;

	. = 0x0; /*SRAM START ADDRES*/
	.bss : 
	{
		__bss_start  = .;
        *(DTCA_VECTOR_SEC)
        __dtca_start = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		*(B)
		*(B_1)
		*(B_2)
		*(SI) /* SI is kernel stack section*/
	    __bss_end = .;
	} > SRAM

    . = __rodata_end;
	. = ALIGN(4);
	__idata_start = .;
	.data : 
	{
		__data_start = .;
		*(.data)
		*(.data.*)
		*(D)
		*(D_1)
		*(D_2)
	    __data_end = .;
	} > SRAM AT> FLASH
    
	__idata_end = __idata_start + SIZEOF(.data);
	_edata = .;
	PROVIDE(edata = .);

    . = ALIGN(4);
    .option_mem 0x00120040 : 
    {
      *(.option_memory)
    } > OPTION_FLASH
     
	. = ALIGN(4);
    .fvectors 0xFFFFFF80 :
   {
      *(.fvect)
    } > FLASH
	_end = .;
	PROVIDE(end = .);
}
