/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if TKERNEL_PRID != 0x07u
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives (#include)
 */

#include "target_timer.h"
#include "target_edmac.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "syssvc/logtask.h"
#include "sample1.h"

/*
 *  Default Definitions of Trace Log Macros
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(intno)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(intno)
#endif /* LOG_ISR_LEAVE */

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_LOGTASK[COUNT_STK_T(LOGTASK_STACK_SIZE)];
static STK_T _kernel_stack_TASK1[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_TASK2[COUNT_STK_T(NET_STACK_SIZE)];
static STK_T _kernel_stack_TASK3[COUNT_STK_T(NET_STACK_SIZE)];
static STK_T _kernel_stack_TASK4[COUNT_STK_T(NET_STACK_SIZE)];
static STK_T _kernel_stack_MAIN_TASK[COUNT_STK_T(STACK_SIZE)];

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID), ((TASK)(logtask_main)), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK, (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(1), ((TASK)(task)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1, (TA_NULL), (tex_routine) },
	{ (TA_NULL), (intptr_t)(2), ((TASK)(taskEther)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(NET_STACK_SIZE), _kernel_stack_TASK2, (TA_NULL), (tex_routine) },
	{ (TA_NULL), (intptr_t)(3), ((TASK)(taskDemoWolf)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(NET_STACK_SIZE), _kernel_stack_TASK3, (TA_NULL), (tex_routine) },
	{ (TA_NULL), (intptr_t)(4), ((TASK)(taskNetWork)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(NET_STACK_SIZE), _kernel_stack_TASK4, (TA_NULL), (tex_routine) },
	{ (TA_ACT), (intptr_t)(0), ((TASK)(main_task)), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK, (TA_NULL), (NULL) }
};

TCB _kernel_tcb_table[TNUM_TSKID];

const ID _kernel_torder_table[TNUM_TSKID] = {
	LOGTASK, TASK1, TASK2, TASK3, TASK4, MAIN_TASK
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_TPRI), (0), (1) }
};

SEMCB _kernel_semcb_table[TNUM_SEMID];

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
TOPPERS_EMPTY_LABEL(FLGCB, _kernel_flgcb_table);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);
TOPPERS_EMPTY_LABEL(DTQCB, _kernel_dtqcb_table);

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB, _kernel_pdqcb_table);

/*
 *  Mailbox Functions
 */

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

TOPPERS_EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
TOPPERS_EMPTY_LABEL(MBXCB, _kernel_mbxcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);

/*
 *  Cyclic Handler Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{ (TA_NULL), (intptr_t)(0), (cyclic_handler), (2000), (0) }
};

CYCCB _kernel_cyccb_table[TNUM_CYCID];

/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {
	{ (TA_NULL), (intptr_t)(0), (alarm_handler) }
};

ALMCB _kernel_almcb_table[TNUM_ALMID];

/*
 *  Interrupt Management Functions
 */


#define TNUM_INHNO	4
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_TIMER, 28, target_timer_handler)
INTHDR_ENTRY(INHNO_TIMER_CMT1, 29, target_timer_cmt1_handler)
INTHDR_ENTRY(INHNO_TIMER_CMT2, 128, target_timer_cmt2_handler)
INTHDR_ENTRY(INHNO_EDMAC_0, 113, rx72n_edmac_interrput_wrapper)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INHNO_TIMER), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER, target_timer_handler)) },
	{ (INHNO_TIMER_CMT1), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_CMT1, target_timer_cmt1_handler)) },
	{ (INHNO_TIMER_CMT2), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_CMT2, target_timer_cmt2_handler)) },
	{ (INHNO_EDMAC_0), (TA_NULL), (FP)(INT_ENTRY(INHNO_EDMAC_0, rx72n_edmac_interrput_wrapper)) }
};

#define TNUM_INTNO	4
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER), (INTATR_TIMER), (INTPRI_TIMER) },
	{ (INTNO_TIMER_CMT1), (INTATR_TIMER), (INTPRI_TIMER) },
	{ (INTNO_TIMER_CMT2), (INTATR_TIMER), (INTPRI_TIMER) },
	{ (INTNO_EDMAC_0), (INTATR_EDMAC_0), (INTPRI_EDMAC_0) }
};

/*
 *  CPU Exception Management Functions
 */

#define TNUM_EXCNO	1
const uint_t _kernel_tnum_excno = TNUM_EXCNO;

EXCHDR_ENTRY(CPUEXC1, 25, cpuexc_handler)

const EXCINIB _kernel_excinib_table[TNUM_EXCNO] = {
	{ (CPUEXC1), (TA_NULL), (FP)(EXC_ENTRY(CPUEXC1, cpuexc_handler)) }
};

/*
 *  Stack Area for Non-task Context
 */

#ifdef DEFAULT_ISTK

#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ
#define TOPPERS_ISTK		DEFAULT_ISTK

#else /* DEAULT_ISTK */

static STK_T _kernel_istack[COUNT_STK_T(DEFAULT_ISTKSZ)];

#define TOPPERS_ISTKSZ		ROUND_STK_T(DEFAULT_ISTKSZ)
#define TOPPERS_ISTK		_kernel_istack

#endif /* DEAULT_ISTK */

const SIZE		_kernel_istksz = TOPPERS_ISTKSZ;
STK_T *const	_kernel_istk = TOPPERS_ISTK;

#ifdef TOPPERS_ISTKPT
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_ISTK, TOPPERS_ISTKSZ);
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_semaphore();
	_kernel_initialize_cyclic();
	_kernel_initialize_alarm();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(target_timer_initialize))((intptr_t)(0));
	((INIRTN)(target_timer_cmt1_initialize))((intptr_t)(0));
	((INIRTN)(target_timer_cmt2_initialize))((intptr_t)(0));
	((INIRTN)(syslog_initialize))((intptr_t)(0));
	((INIRTN)(print_banner))((intptr_t)(0));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(logtask_terminate))((intptr_t)(0));
	((TERRTN)(target_timer_cmt2_terminate))((intptr_t)(0));
	((TERRTN)(target_timer_cmt1_terminate))((intptr_t)(0));
	((TERRTN)(target_timer_terminate))((intptr_t)(0));
}

/*
 *  Interrupt Level and Attribute Table
 */
const CFG_INT_INFO _kernel_cfg_int_table[256] = {
	{  0, 0xFFFFFFFF }, /* 00 */
	{  0, 0xFFFFFFFF }, /* 01 */
	{  0, 0xFFFFFFFF }, /* 02 */
	{  0, 0xFFFFFFFF }, /* 03 */
	{  0, 0xFFFFFFFF }, /* 04 */
	{  0, 0xFFFFFFFF }, /* 05 */
	{  0, 0xFFFFFFFF }, /* 06 */
	{  0, 0xFFFFFFFF }, /* 07 */
	{  0, 0xFFFFFFFF }, /* 08 */
	{  0, 0xFFFFFFFF }, /* 09 */
	{  0, 0xFFFFFFFF }, /* 10 */
	{  0, 0xFFFFFFFF }, /* 11 */
	{  0, 0xFFFFFFFF }, /* 12 */
	{  0, 0xFFFFFFFF }, /* 13 */
	{  0, 0xFFFFFFFF }, /* 14 */
	{  0, 0xFFFFFFFF }, /* 15 */
	{  0, 0xFFFFFFFF }, /* 16 */
	{  0, 0xFFFFFFFF }, /* 17 */
	{  0, 0xFFFFFFFF }, /* 18 */
	{  0, 0xFFFFFFFF }, /* 19 */
	{  0, 0xFFFFFFFF }, /* 20 */
	{  0, 0xFFFFFFFF }, /* 21 */
	{  0, 0xFFFFFFFF }, /* 22 */
	{  0, 0xFFFFFFFF }, /* 23 */
	{  0, 0xFFFFFFFF }, /* 24 */
	{  0, 0xFFFFFFFF }, /* 25 */
	{  0, 0xFFFFFFFF }, /* 26 */
	{  0, 0xFFFFFFFF }, /* 27 */
	{  5, INTATR_TIMER }, /* 28 */
	{  5, INTATR_TIMER }, /* 29 */
	{  0, 0xFFFFFFFF }, /* 30 */
	{  0, 0xFFFFFFFF }, /* 31 */
	{  0, 0xFFFFFFFF }, /* 32 */
	{  0, 0xFFFFFFFF }, /* 33 */
	{  0, 0xFFFFFFFF }, /* 34 */
	{  0, 0xFFFFFFFF }, /* 35 */
	{  0, 0xFFFFFFFF }, /* 36 */
	{  0, 0xFFFFFFFF }, /* 37 */
	{  0, 0xFFFFFFFF }, /* 38 */
	{  0, 0xFFFFFFFF }, /* 39 */
	{  0, 0xFFFFFFFF }, /* 40 */
	{  0, 0xFFFFFFFF }, /* 41 */
	{  0, 0xFFFFFFFF }, /* 42 */
	{  0, 0xFFFFFFFF }, /* 43 */
	{  0, 0xFFFFFFFF }, /* 44 */
	{  0, 0xFFFFFFFF }, /* 45 */
	{  0, 0xFFFFFFFF }, /* 46 */
	{  0, 0xFFFFFFFF }, /* 47 */
	{  0, 0xFFFFFFFF }, /* 48 */
	{  0, 0xFFFFFFFF }, /* 49 */
	{  0, 0xFFFFFFFF }, /* 50 */
	{  0, 0xFFFFFFFF }, /* 51 */
	{  0, 0xFFFFFFFF }, /* 52 */
	{  0, 0xFFFFFFFF }, /* 53 */
	{  0, 0xFFFFFFFF }, /* 54 */
	{  0, 0xFFFFFFFF }, /* 55 */
	{  0, 0xFFFFFFFF }, /* 56 */
	{  0, 0xFFFFFFFF }, /* 57 */
	{  0, 0xFFFFFFFF }, /* 58 */
	{  0, 0xFFFFFFFF }, /* 59 */
	{  0, 0xFFFFFFFF }, /* 60 */
	{  0, 0xFFFFFFFF }, /* 61 */
	{  0, 0xFFFFFFFF }, /* 62 */
	{  0, 0xFFFFFFFF }, /* 63 */
	{  0, 0xFFFFFFFF }, /* 64 */
	{  0, 0xFFFFFFFF }, /* 65 */
	{  0, 0xFFFFFFFF }, /* 66 */
	{  0, 0xFFFFFFFF }, /* 67 */
	{  0, 0xFFFFFFFF }, /* 68 */
	{  0, 0xFFFFFFFF }, /* 69 */
	{  0, 0xFFFFFFFF }, /* 70 */
	{  0, 0xFFFFFFFF }, /* 71 */
	{  0, 0xFFFFFFFF }, /* 72 */
	{  0, 0xFFFFFFFF }, /* 73 */
	{  0, 0xFFFFFFFF }, /* 74 */
	{  0, 0xFFFFFFFF }, /* 75 */
	{  0, 0xFFFFFFFF }, /* 76 */
	{  0, 0xFFFFFFFF }, /* 77 */
	{  0, 0xFFFFFFFF }, /* 78 */
	{  0, 0xFFFFFFFF }, /* 79 */
	{  0, 0xFFFFFFFF }, /* 80 */
	{  0, 0xFFFFFFFF }, /* 81 */
	{  0, 0xFFFFFFFF }, /* 82 */
	{  0, 0xFFFFFFFF }, /* 83 */
	{  0, 0xFFFFFFFF }, /* 84 */
	{  0, 0xFFFFFFFF }, /* 85 */
	{  0, 0xFFFFFFFF }, /* 86 */
	{  0, 0xFFFFFFFF }, /* 87 */
	{  0, 0xFFFFFFFF }, /* 88 */
	{  0, 0xFFFFFFFF }, /* 89 */
	{  0, 0xFFFFFFFF }, /* 90 */
	{  0, 0xFFFFFFFF }, /* 91 */
	{  0, 0xFFFFFFFF }, /* 92 */
	{  0, 0xFFFFFFFF }, /* 93 */
	{  0, 0xFFFFFFFF }, /* 94 */
	{  0, 0xFFFFFFFF }, /* 95 */
	{  0, 0xFFFFFFFF }, /* 96 */
	{  0, 0xFFFFFFFF }, /* 97 */
	{  0, 0xFFFFFFFF }, /* 98 */
	{  0, 0xFFFFFFFF }, /* 99 */
	{  0, 0xFFFFFFFF }, /* 100 */
	{  0, 0xFFFFFFFF }, /* 101 */
	{  0, 0xFFFFFFFF }, /* 102 */
	{  0, 0xFFFFFFFF }, /* 103 */
	{  0, 0xFFFFFFFF }, /* 104 */
	{  0, 0xFFFFFFFF }, /* 105 */
	{  0, 0xFFFFFFFF }, /* 106 */
	{  0, 0xFFFFFFFF }, /* 107 */
	{  0, 0xFFFFFFFF }, /* 108 */
	{  0, 0xFFFFFFFF }, /* 109 */
	{  0, 0xFFFFFFFF }, /* 110 */
	{  0, 0xFFFFFFFF }, /* 111 */
	{  0, 0xFFFFFFFF }, /* 112 */
	{  5, INTATR_EDMAC_0 }, /* 113 */
	{  0, 0xFFFFFFFF }, /* 114 */
	{  0, 0xFFFFFFFF }, /* 115 */
	{  0, 0xFFFFFFFF }, /* 116 */
	{  0, 0xFFFFFFFF }, /* 117 */
	{  0, 0xFFFFFFFF }, /* 118 */
	{  0, 0xFFFFFFFF }, /* 119 */
	{  0, 0xFFFFFFFF }, /* 120 */
	{  0, 0xFFFFFFFF }, /* 121 */
	{  0, 0xFFFFFFFF }, /* 122 */
	{  0, 0xFFFFFFFF }, /* 123 */
	{  0, 0xFFFFFFFF }, /* 124 */
	{  0, 0xFFFFFFFF }, /* 125 */
	{  0, 0xFFFFFFFF }, /* 126 */
	{  0, 0xFFFFFFFF }, /* 127 */
	{  5, INTATR_TIMER }, /* 128 */
	{  0, 0xFFFFFFFF }, /* 129 */
	{  0, 0xFFFFFFFF }, /* 130 */
	{  0, 0xFFFFFFFF }, /* 131 */
	{  0, 0xFFFFFFFF }, /* 132 */
	{  0, 0xFFFFFFFF }, /* 133 */
	{  0, 0xFFFFFFFF }, /* 134 */
	{  0, 0xFFFFFFFF }, /* 135 */
	{  0, 0xFFFFFFFF }, /* 136 */
	{  0, 0xFFFFFFFF }, /* 137 */
	{  0, 0xFFFFFFFF }, /* 138 */
	{  0, 0xFFFFFFFF }, /* 139 */
	{  0, 0xFFFFFFFF }, /* 140 */
	{  0, 0xFFFFFFFF }, /* 141 */
	{  0, 0xFFFFFFFF }, /* 142 */
	{  0, 0xFFFFFFFF }, /* 143 */
	{  0, 0xFFFFFFFF }, /* 144 */
	{  0, 0xFFFFFFFF }, /* 145 */
	{  0, 0xFFFFFFFF }, /* 146 */
	{  0, 0xFFFFFFFF }, /* 147 */
	{  0, 0xFFFFFFFF }, /* 148 */
	{  0, 0xFFFFFFFF }, /* 149 */
	{  0, 0xFFFFFFFF }, /* 150 */
	{  0, 0xFFFFFFFF }, /* 151 */
	{  0, 0xFFFFFFFF }, /* 152 */
	{  0, 0xFFFFFFFF }, /* 153 */
	{  0, 0xFFFFFFFF }, /* 154 */
	{  0, 0xFFFFFFFF }, /* 155 */
	{  0, 0xFFFFFFFF }, /* 156 */
	{  0, 0xFFFFFFFF }, /* 157 */
	{  0, 0xFFFFFFFF }, /* 158 */
	{  0, 0xFFFFFFFF }, /* 159 */
	{  0, 0xFFFFFFFF }, /* 160 */
	{  0, 0xFFFFFFFF }, /* 161 */
	{  0, 0xFFFFFFFF }, /* 162 */
	{  0, 0xFFFFFFFF }, /* 163 */
	{  0, 0xFFFFFFFF }, /* 164 */
	{  0, 0xFFFFFFFF }, /* 165 */
	{  0, 0xFFFFFFFF }, /* 166 */
	{  0, 0xFFFFFFFF }, /* 167 */
	{  0, 0xFFFFFFFF }, /* 168 */
	{  0, 0xFFFFFFFF }, /* 169 */
	{  0, 0xFFFFFFFF }, /* 170 */
	{  0, 0xFFFFFFFF }, /* 171 */
	{  0, 0xFFFFFFFF }, /* 172 */
	{  0, 0xFFFFFFFF }, /* 173 */
	{  0, 0xFFFFFFFF }, /* 174 */
	{  0, 0xFFFFFFFF }, /* 175 */
	{  0, 0xFFFFFFFF }, /* 176 */
	{  0, 0xFFFFFFFF }, /* 177 */
	{  0, 0xFFFFFFFF }, /* 178 */
	{  0, 0xFFFFFFFF }, /* 179 */
	{  0, 0xFFFFFFFF }, /* 180 */
	{  0, 0xFFFFFFFF }, /* 181 */
	{  0, 0xFFFFFFFF }, /* 182 */
	{  0, 0xFFFFFFFF }, /* 183 */
	{  0, 0xFFFFFFFF }, /* 184 */
	{  0, 0xFFFFFFFF }, /* 185 */
	{  0, 0xFFFFFFFF }, /* 186 */
	{  0, 0xFFFFFFFF }, /* 187 */
	{  0, 0xFFFFFFFF }, /* 188 */
	{  0, 0xFFFFFFFF }, /* 189 */
	{  0, 0xFFFFFFFF }, /* 190 */
	{  0, 0xFFFFFFFF }, /* 191 */
	{  0, 0xFFFFFFFF }, /* 192 */
	{  0, 0xFFFFFFFF }, /* 193 */
	{  0, 0xFFFFFFFF }, /* 194 */
	{  0, 0xFFFFFFFF }, /* 195 */
	{  0, 0xFFFFFFFF }, /* 196 */
	{  0, 0xFFFFFFFF }, /* 197 */
	{  0, 0xFFFFFFFF }, /* 198 */
	{  0, 0xFFFFFFFF }, /* 199 */
	{  0, 0xFFFFFFFF }, /* 200 */
	{  0, 0xFFFFFFFF }, /* 201 */
	{  0, 0xFFFFFFFF }, /* 202 */
	{  0, 0xFFFFFFFF }, /* 203 */
	{  0, 0xFFFFFFFF }, /* 204 */
	{  0, 0xFFFFFFFF }, /* 205 */
	{  0, 0xFFFFFFFF }, /* 206 */
	{  0, 0xFFFFFFFF }, /* 207 */
	{  0, 0xFFFFFFFF }, /* 208 */
	{  0, 0xFFFFFFFF }, /* 209 */
	{  0, 0xFFFFFFFF }, /* 210 */
	{  0, 0xFFFFFFFF }, /* 211 */
	{  0, 0xFFFFFFFF }, /* 212 */
	{  0, 0xFFFFFFFF }, /* 213 */
	{  0, 0xFFFFFFFF }, /* 214 */
	{  0, 0xFFFFFFFF }, /* 215 */
	{  0, 0xFFFFFFFF }, /* 216 */
	{  0, 0xFFFFFFFF }, /* 217 */
	{  0, 0xFFFFFFFF }, /* 218 */
	{  0, 0xFFFFFFFF }, /* 219 */
	{  0, 0xFFFFFFFF }, /* 220 */
	{  0, 0xFFFFFFFF }, /* 221 */
	{  0, 0xFFFFFFFF }, /* 222 */
	{  0, 0xFFFFFFFF }, /* 223 */
	{  0, 0xFFFFFFFF }, /* 224 */
	{  0, 0xFFFFFFFF }, /* 225 */
	{  0, 0xFFFFFFFF }, /* 226 */
	{  0, 0xFFFFFFFF }, /* 227 */
	{  0, 0xFFFFFFFF }, /* 228 */
	{  0, 0xFFFFFFFF }, /* 229 */
	{  0, 0xFFFFFFFF }, /* 230 */
	{  0, 0xFFFFFFFF }, /* 231 */
	{  0, 0xFFFFFFFF }, /* 232 */
	{  0, 0xFFFFFFFF }, /* 233 */
	{  0, 0xFFFFFFFF }, /* 234 */
	{  0, 0xFFFFFFFF }, /* 235 */
	{  0, 0xFFFFFFFF }, /* 236 */
	{  0, 0xFFFFFFFF }, /* 237 */
	{  0, 0xFFFFFFFF }, /* 238 */
	{  0, 0xFFFFFFFF }, /* 239 */
	{  0, 0xFFFFFFFF }, /* 240 */
	{  0, 0xFFFFFFFF }, /* 241 */
	{  0, 0xFFFFFFFF }, /* 242 */
	{  0, 0xFFFFFFFF }, /* 243 */
	{  0, 0xFFFFFFFF }, /* 244 */
	{  0, 0xFFFFFFFF }, /* 245 */
	{  0, 0xFFFFFFFF }, /* 246 */
	{  0, 0xFFFFFFFF }, /* 247 */
	{  0, 0xFFFFFFFF }, /* 248 */
	{  0, 0xFFFFFFFF }, /* 249 */
	{  0, 0xFFFFFFFF }, /* 250 */
	{  0, 0xFFFFFFFF }, /* 251 */
	{  0, 0xFFFFFFFF }, /* 252 */
	{  0, 0xFFFFFFFF }, /* 253 */
	{  0, 0xFFFFFFFF }, /* 254 */
	{  0, 0xFFFFFFFF }, /* 255 */
};


