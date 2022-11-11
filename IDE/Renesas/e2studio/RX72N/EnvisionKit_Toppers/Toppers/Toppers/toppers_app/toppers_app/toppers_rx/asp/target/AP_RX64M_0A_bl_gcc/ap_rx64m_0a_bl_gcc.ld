MEMORY
{
    SRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 512K
    SDRAM (rwx) : ORIGIN = 0x08000000, LENGTH = 8M
}

PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);
STARTUP(start.o)
ENTRY(_start)

SECTIONS
{

	.text :
	{
		__text = .;
		*(.vector)
		*(.text)
		*(.text.*)
		*(P)
	} > SDRAM
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
	} > SDRAM
    __rodata_end = .;
	__exidx_start = .;
	__exidx_end = .;

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
	} > SDRAM 
    
	__idata_end = __idata_start + SIZEOF(.data);
	_edata = .;
	PROVIDE(edata = .);
    
	.bss : 
	{
		__bss_start  = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		*(B)
		*(B_1)
		*(B_2)
		*(SI) /* SI is kernel stack section*/
	    __bss_end = .;
	} > SDRAM

    .dtca_vect 0x0 :
   {
      *(DTCA_VECTOR_SEC)
    } > SRAM
    
	_end = .;
	PROVIDE(end = .);
}
