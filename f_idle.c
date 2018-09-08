

#include	"STC15W4K60S4.H"

#include	"const.h"
#include	"ptype.h"
#include 	"macro.h"
#include 	"global.h"
#include 	"arch.h"
#include 	"driver.h"
#include	"main.h"

#include    "f_idle.h"
#include    "f_poweron.h"

int f_idle(void *pMsg)
{
    func_t func;
	//u8	tmp;
	
    switch(((msg_t *)pMsg)->msgType) 
	{
	case CACT_OVER:
		break;

	case CMSG_TMR:
		break;
	
	
	case CMSG_PWON:
		/** 上电消息 **/
	#if	1
		fstack_init(&g_fstack);
		func.func = f_idle;
		fstack_push(&g_fstack, &func);
			
		g_tick = 0;
		SetTimer_irq(&g_timer[0], CTIMER_100MS, CMSG_INIT);
	#endif
		break;
	
	default:
		break;
	}
	
    return  0;
}
