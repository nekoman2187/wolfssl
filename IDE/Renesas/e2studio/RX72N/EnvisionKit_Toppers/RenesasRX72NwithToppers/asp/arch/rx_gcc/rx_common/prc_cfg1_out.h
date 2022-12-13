/*
 *		cfg1_out.cのリンクに必要なスタブの定義
 */

void sta_ker( void )
{
}

STK_T *const	_kernel_istkpt = 0x00;

void hardware_init_hook( void )
{
}

void software_init_hook( void )
{
}

const SIZE		_kernel_istksz = 0;

STK_T *const	_kernel_istk = NULL;

uint32_t *const _vvector_table = 0x00;

/* 
 *  オフセットファイルを生成するための定義 
 */ 
const uint8_t   MAGIC_1 = 0x12; 
const uint16_t  MAGIC_2 = 0x1234; 
const uint32_t  MAGIC_4 = 0x12345678;

const TCB	TCB_enatex = {
	{ NULL, NULL },			/* task_queue */
	NULL,					/* p_tinib */
	0U,						/* tstat */
#ifdef TOPPERS_SUPPORT_MUTEX
	0U,						/* bpriority */
#endif /* TOPPERS_SUPPORT_MUTEX */
	0U,						/* priority */
	false,					/* acqeue */
	false,					/* wupque */
	true,					/* enatex */
	0U,						/* texprn */
	NULL,					/* p_winifo */
#ifdef TOPPERS_SUPPORT_MUTEX
	{ NULL, NULL },			/* mutex_queue */
#endif /* TOPPERS_SUPPORT_MUTEX */
	{ NULL, NULL }			/* tskctxb */
};
