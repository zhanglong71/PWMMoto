
//#include	<reg52.h>
#include	"STC15W4K60S4.H"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
//#include "debug.h"
#include "arch.h"


/*******************************************************************************
 *
 * function stack operation
 *
 * 栈顶指针的范围：0..STACKSIZE(=8)
 * 0 - 栈空(无数据，可存放数据)
 * STACKSIZE - 栈满(不能再存放更多数据，可取数据)
 *******************************************************************************/
void fstack_init(fstack_t *s)
{
	s->top = 0;
}

#if	0
int	fstack_pop(fstack_t *s)
{
	if((s->top <= 0) || (s->top > STACKSIZE)) {    /** make sure ... top [1..STACKSIZE - 1]  **/
		return	FALSE;
	}
	
	s->top--;
	return	TRUE;
}
#endif

int	fstack_push(fstack_t *s, func_t *f)   /** make sure ... top [0..STACKSIZE-2]  **/

{
	if(s->top >= STACKSIZE) {
		/**
			s->func[s->top].func = f->func;
			s->func[s->top].arg = f->arg;
		**/
		return	FALSE;
	}
	s->func[s->top].func = f->func;
	s->func[s->top].arg = f->arg;
	s->top++;
	
	return	TRUE;
}

#if	0
int fstack_update(fstack_t *s, func_t *f)
{
	/** Same As: stackpop()/stackpush() **/
	if(s->top > 0) {
		s->func[s->top - 1].func = f->func;
		s->func[s->top - 1].arg = f->arg;
	}
	return	TRUE;
}
#endif
/**
 * get the data at the top of the stack
 *
 **/
int	fstack_top(const fstack_t *s, func_t *f)   /** make sure ... top [1..STACKSIZE - 1]  **/
{
	if((s->top < 1) || (s->top > STACKSIZE)) {
		return	FALSE;
	}
	f->func = s->func[s->top - 1].func;
	f->arg = s->func[s->top - 1].arg;

	return	TRUE;
}

/*******************************************************************************
 *
 * msg queue operation
 *
 *******************************************************************************/
int msg_init(msg_t *pMsg)
{
	if((pMsg != 0)) {
		pMsg->msgType = CMSG_NONE;
		return	TRUE;
	} else {
		return	FALSE;
	}
}

void msgq_init(msgq_t *q)
{
	q->tail = q->head = 0;
}

static int isempty(msgq_t *q)
{
	if(q->tail == q->head) {
		return TRUE;
	}
	return	FALSE;
}

static int isfull(msgq_t *q)
{
	if((q->tail + 1 == q->head) || (((q->tail + 1) % QUEUESIZE) == (q->head))) {
		return TRUE;
	}
	return	FALSE;
}

int	msgq_in(msgq_t *q, msg_t *val)		    //Note: check queue full is necessary before invoke this routine
{
    if(isfull(q)) {
        return  FALSE;
    }
    
	q->msg[q->tail].msgType = val->msgType;	
	q->msg[q->tail].msgValue = val->msgValue;
	
	q->tail = (q->tail + 1) % QUEUESIZE;

	return TRUE;
}

#if	0
int	msgq_in_irq(msgq_t *q, msg_t *val)		//Note: check queue full is necessary before invoke this routine
{
    int iRet;
    
    EA = 0;
    iRet = msgq_in(q, val);
    EA = 1;

	return iRet;
}
#endif

int	msgq_out(msgq_t *q, msg_t *val)		//Note: check queue empty is necessary before invoke this routine
{
    if(isempty(q)) {
        return  FALSE;
    }
    
	val->msgType = q->msg[q->head].msgType;
	val->msgValue = q->msg[q->head].msgValue;
	q->head = (q->head + 1) % QUEUESIZE;
	    
	return	TRUE;
}

int	msgq_out_irq(msgq_t *q, msg_t *val)		//Note: check queue empty is necessary before invoke this routine
{
    int iRet;
    
    EA = 0;
    iRet = msgq_out(q, val);
	EA = 1;
	    
	return	iRet;
}

/*******************************************************************************
 * Timer operation
 *******************************************************************************/
void SetTimer(Timer_t * timer, int tick, msgType_t msgType)
{
    timer->tick = tick;
    timer->tick_bak = tick;
    timer->msgType = msgType;
}
void SetTimer_irq(Timer_t * timer, int tick, msgType_t msgType)
{
    EA = 0;
    SetTimer(timer, tick, msgType);
    EA = 1;
}

void ClrTimer(Timer_t * timer)
{
    timer->tick = 0;
    timer->tick_bak = 0;
}
void ClrTimer_irq(Timer_t * timer)
{
    EA = 0;
    ClrTimer(timer);
    EA = 1;
}
/*******************************************************************************
 * delay() operation
 * 
 * wait until timer out
 *******************************************************************************/
 
 #if	0
int g_tmr_delay;

void delay(int TickCount)
{
    g_tmr_delay = TickCount;
    
    while(g_tmr_delay);
}
#endif
/***************************************
 * delay
 ***************************************/
 #if	0
void delaySpin(u32 _loop)
{
	while(_loop-- > 0);
}

/** 1us(没关中断，至少1us) **/
void delaySpin_us(u32 _us)
{
	for(; _us > 0; _us--)delaySpin(24);
}

/** 1ms(没关中断，至少1ms) **/
void delaySpin_ms(u32 _ms)
{
	for(; _ms > 0; _ms--)delaySpin(237);
}
#endif

#if	0
/*******************************************************************************/
void atomic_set(short *_var, short _value)
{
	IRQ_disable();
	*_var = _value;
    IRQ_enable();
}

short atomic_get(short *_var)
{
	short tmp;
	
	IRQ_disable();
	tmp = *_var;
    IRQ_enable();
    
    return	tmp;
}
#endif


/*******************************************************************************
 * check is the queue empty
 *******************************************************************************/
static int isActionQueEmpty(actionQueue_t *q)
{
	if(q->tail == q->head)
	{
		return TRUE;
	}
	return	FALSE;
}

/*******************************************************************************
 * check is the queue full
 *******************************************************************************/
static int isActionQueFull(actionQueue_t *q)
{
	if((q->tail + 1 == q->head) || (((q->tail + 1) % ACTIONQUEUESIZE) == q->head))
	{
		return TRUE;
	}
	return	FALSE;
}

#if	0
/*******************************************************************************/
void adcSample_Init(adcData_t *adcData, Timer_t *timer, msgType_t stepMsgType, int tick)
{
	adcData->u16count = 0;
	adcData->u16currValue = 0;
	adcData->u16average = 0;
	
	adcData->stepMsgType = stepMsgType;
	adcData->tick = tick;
	adcData->timer = timer;
	ClrTimer(timer);
	
	g_flag &= (~(1<<8));
	g_flag &= (~(1<<9));
}
#endif

/*******************
 * ADC
 *******************/

#if	0
int adcSample_In(adcData_t *adcData, u16 __value)
{
	adcData->u16count += 1;
	adcData->u16currValue = __value;
	
	adcData->u16average = (((adcData->u16count - 1) * (adcData->u16average)) + __value)/(adcData->u16count);	//重新计算均值
	
    return TRUE;
}

int adcSample_Out(adcData_t *adcData, u16 *__average)
{
	if(adcData->u16count >= 16) {
		if(__average != 0) {
			*__average = adcData->u16average;	//取均值
		}
    	return TRUE;
	}
    return	FALSE;
}
#endif

/*******************************************************************************
 * put the data into the (loop)queue
 *******************************************************************************/
void actionQueueInit(actionQueue_t *q, Timer_t *timer, msgType_t stepMsgType, msgType_t overMsgType)
{
	q->tail = q->head = 0;
	
	q->stepMsgType = stepMsgType;  
	q->overMsgType = overMsgType;
	q->timer = timer;
	q->flag = 0;
	ClrTimer(q->timer);
}

/*******************************************************************************
 * put the data into the (loop)queue
 *******************************************************************************/
int actionQueueIn(actionQueue_t *q, action_t *action)
{
    if(isActionQueFull(q)) {
        return	FALSE;
    }

    q->buf[q->tail].actionType = action->actionType;
    q->buf[q->tail].actionTime = action->actionTime;
    q->buf[q->tail].actionPara = action->actionPara;
    q->buf[q->tail].func       = action->func;
	q->tail = (q->tail + 1) % ACTIONQUEUESIZE;
    
    return TRUE;
}

int actionQueueOut(actionQueue_t *q, action_t *action)
{
    if(isActionQueEmpty(q)) {
        return	FALSE;
    }
    
    action->actionType = q->buf[q->head].actionType;
    action->actionTime = q->buf[q->head].actionTime;
    action->actionPara = q->buf[q->head].actionPara;
    action->func       = q->buf[q->head].func;
    
	q->head = (q->head + 1) % ACTIONQUEUESIZE;
       
    return TRUE;
}

/*******************************************************************************
 * 动作处理: 启动新的动作
 *******************************************************************************/
static void startAction(actionQueue_t *q, action_t * pAction)
{
	
	SetTimer_irq(q->timer, pAction->actionTime, q->stepMsgType);
	
	switch(pAction->actionType)
	{
	case	CACT_MOT1NORM:
	case	CACT_MOT1REVE:
	case	CACT_MOT1WAIT:
		q->flag = (1 << 7);
		if(pAction->func != 0)(pAction->func)();
		break;
	
	case	CACT_MOT2NORM:
	case	CACT_MOT2REVE:
	case	CACT_MOT2WAIT:
		q->flag = (1 << 6);
		if(pAction->func != 0)(pAction->func)();
		break;
	
	case	CACT_MOT3NORM:
	case	CACT_MOT3REVE:
	case	CACT_MOT3WAIT:
		
		q->flag = (1 << 5);
		if(pAction->func != 0)(pAction->func)();
		break;
	
	case	CACT_MOT4NORM:
	case	CACT_MOT4REVE:
	case	CACT_MOT4WAIT:
		
		q->flag = (1 << 4);
		if(pAction->func != 0)(pAction->func)();
		break;
	
	case	CACT_MOT5NORM:
	case	CACT_MOT5REVE:
	case	CACT_MOT5WAIT:
		
		q->flag = (1 << 3);
		if(pAction->func != 0)(pAction->func)();
		break;
	
	case	CACT_MOT6NORM:
	case	CACT_MOT6REVE:
	case	CACT_MOT6WAIT:
		
		q->flag = (1 << 2);
		if(pAction->func != 0)(pAction->func)();
		break;
	/** LED亮度 **/
	case	CACT_PWMLED:
		q->flag = (1 << 1);
		
		if(pAction->func != 0)((paction_t_1)(pAction->func))((u8)pAction->actionPara);
		break;
	
	/** 指示灯提示闪烁(在sys处理结束消息) **/
	case	CACT_MISC:
		q->flag = (1 << 0);
		if(pAction->func != 0)pAction->func();
		break;
			
	default:
		/** 不可识别的动作 **/
		q->flag = 0;
		break;
	}
}

/*******************************************************************************
 * 动作处理：停止当前的动作
 * 只需要清除定时器，清除标记即可(忘记了可以这样处理的原因，什么时候想起，记得补上)
 *
 * 特殊动作需要指定标记清除用
 *
 * 考虑将停止动作本身当成一个动作处理，则此处可不做任何动作
 ********************************************************************************/
static void stopAction(actionQueue_t *q)
{
	ClrTimer_irq(q->timer);
	/** stop the timeout action  **/
	if(q->flag & (1)) {
	/** misc **/
		q->flag &= ~(1);
	} else {
		/** misc **/
		q->flag = 0;
	}
}

/** 事件队列处理 **/
void actionDoing(actionQueue_t * q)
{
	action_t action;
	
	if(q->flag == 0)
	{
		if(actionQueueOut(q, &action) == TRUE)
		{
			startAction(q, &action);
		}
	}
}

/** 系统当前事件结束, 处理下一个 **/
void actProcess(actionQueue_t * q)
{
	action_t action;
	
	/** stop the timeout action first  **/
	stopAction(q);
	
	/** start the next action **/
	if(actionQueueOut(q, &action) == TRUE) {
		startAction(q, &action);
	} else {
		q->flag = 0;
		SetTimer_irq(q->timer, CTIMER_10MS, q->overMsgType);
	}
}

/*******************************************************************************/

/*******************************************************************************
 * check is the queue empty
 *******************************************************************************/
static int isCharQueEmpty(charQueue_t *q)
{
	if(q->tail == q->head)
	{
		return TRUE;
	}
	return	FALSE;
}

/*******************************************************************************
 * check is the queue full
 *******************************************************************************/
static int isCharQueFull(charQueue_t *q)
{
	if((q->tail + 1 == q->head) || (((q->tail + 1) % CHARQUEUESIZE) == q->head))
	{
		return TRUE;
	}
	return	FALSE;
}
/*******************************************************************************
 * put the data into the (loop)queue
 *******************************************************************************/
void charQueueInit(charQueue_t *q)
{
	q->tail = q->head = 0;
}

#if	1		//uart inturrupt  use it for receive data.  do it in MACRO
/*******************************************************************************
 * put the data into the (loop)queue 
 * only for uart RX interrupt
 *******************************************************************************/
int charQueueIn(charQueue_t *q, char ch)	
{
    if(isCharQueFull(q)) {
        return	FALSE;
    }

    q->buf[q->tail]      = ch;
	q->tail = (q->tail + 1) % CHARQUEUESIZE;
    
    return TRUE;
}

int charQueueIn_irq(charQueue_t *q, char ch)	
{
	int iRet;

	EA = 0;
	iRet = charQueueIn(q, ch);
	EA = 1;
   
    return iRet;
}


#endif

int charQueueOut(charQueue_t *q, char *ch)
{
    if(isCharQueEmpty(q)) {
        return	FALSE;
    }
 
    *ch       = q->buf[q->head];
	q->head = ((q->head + 1) % CHARQUEUESIZE);
       
    return TRUE;
}

int charQueueOut_irq(charQueue_t *q, char* ch)
{
	int iRet;
	
	EA = 0;
	iRet = charQueueOut(q, ch);
	EA = 1;
    
    return iRet;
}


int charQueueMove(charQueue_t *from, charQueue_t *to)
{
	u8 ch;
	int iRet = FALSE;
	
    if(isCharQueEmpty(from) == FALSE) {
        while(charQueueOut(from, &ch) == TRUE) {
        	charQueueIn(to, ch);
        }
		
        iRet = TRUE;
    }
    
    return iRet;
}

/**
 * same as charQueueMove()  
 * disable interrupt
 **/
int charQueueMove_irq(charQueue_t *from, charQueue_t *to)
{
	int iRet;
	
	EA = 0;  
	iRet  = charQueueMove(from, to);
    EA = 1;
    
    return iRet;
}

/////////////////////////////////////////////////////
