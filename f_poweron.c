
#include	"STC15W4K60S4.H"

#include	"const.h"
#include	"ptype.h"
#include 	"macro.h"
#include 	"global.h"
#include 	"arch.h"
#include 	"driver.h"
#include	"main.h"
#include 	"moto.h"

#include "f_idle.h"
#include "f_poweron.h"

/*******************************************************************************
 * password function
 *******************************************************************************/
 u8	stepCnt = 0;
int f_poweron(void *pMsg)
{
    func_t func;
	u8	u8tmp = 0;

    switch(((msg_t *)pMsg)->msgType)
	{
	case CMSG_TMR:
		g_tick++;  
		if(g_tick > 10) {
			g_tick = 0;
			SetTimer_irq(&g_timer[0], CTIMER_1SEC, CMSG_INIT);
       		
    		fstack_init(&g_fstack);
			func.func = f_idle;    		
			fstack_push(&g_fstack, &func);
		}
		break;
		
	case CMSG_INIT:		/** 初始化 **/
		g_tick = 0;
		SetTimer_irq(&g_timer[0], CTIMER_1SEC, CMSG_TMR);
	
		setNeck_LRstepCntFlag(1);	//---步进计数
		setNeck_LRSpeed(15);
		setNeck_left();
		break;
	
	case CMSG_MOTO:		//---到达左/右边界	
		setNeck_LRstop(1);
//		setNeck_LRstepCnt(g_stepMot_stat.buf[4].stepLimit);	//---设置步进上限
	
		break;
	case CMSG_IO:		//---到达左/右边界	
		setNeck_LRstop(1);
		u8tmp = io_detect();
	
		if(u8tmp & (1 << 1)) {			//---右边界
			//setNeck_LRstep(getNeck_LRstepCnt() >> 1);
//			setNeck_LRstepLimit(getNeck_LRstepCnt() >> 1);
			
			setNeck_LRstepCntFlag(2);		//---步进上限生效
//			setNeck_LRstepCnt(getNeck_LRstepLimit());
			//setNeck_LRstepCnt(g_LRstep);	//---设置步进上限
			
			setNeck_LRSpeed(15);
			setNeck_left();
		} else if(u8tmp & (1 << 2)) {	//---左边界
//			setNeck_LRstepCnt(0);
			
			setNeck_LRSpeed(15);
			setNeck_right();
		}
	
		break;
	
	
	default:
		break;
	}  

    return  0;
}
/////////////////////////////////////////////////////

