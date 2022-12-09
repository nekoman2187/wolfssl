MEMORY
{
	RAM : ORIGIN = 0x4, LENGTH = 0x7fffc
	RAM2 : ORIGIN = 0x00800000, LENGTH = 524288
	ROM : ORIGIN = 0xFFE00000, LENGTH = 2097152

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
	} > ROM
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
	} > ROM
    __rodata_end = .;
	__exidx_start = .;
	__exidx_end = .;

	. = 0x0; /*RAM START ADDRES*/
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
	} > RAM

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
	} > RAM AT> ROM
    
	__idata_end = __idata_start + SIZEOF(.data);
	_edata = .;
	PROVIDE(edata = .);
    
	. = ALIGN(4);
    .fvectors 0xFFFFFF80 :
   {
      *(.fvect)
    } > ROM
	_end = .;
	PROVIDE(end = .);
}
