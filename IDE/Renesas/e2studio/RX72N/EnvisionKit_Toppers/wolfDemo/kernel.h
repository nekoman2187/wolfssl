#ifndef KERNEL_H
#define KERNEL_H
/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include <stdbool.h>
#include <string.h>
#include "platform.h"
#include "r_t4_driver_rx_config.h"
#include "r_t4_itcpip.h"
#include "r_ether_rx_if.h"
#include "timer.h"

extern ER		get_tid(ID *p_tskid);
extern ER		slp_tsk(void) ;
extern bool		sns_ctx(void);
extern ER		iwup_tsk(ID tskid);
extern ER		wup_tsk(ID tskid) ;
extern ER		iwup_tsk(ID tskid) ;
extern ER		rot_rdq(PRI tskpri);
#define TPRI_SELF		0
#define _RI_CLOCK_TIMER (0)
#define TRUE	true
#endif //KERNEL_H
