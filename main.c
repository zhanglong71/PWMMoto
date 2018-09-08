/**************************************************************************
 *  
 *  项目名称: 机器人行走执行部件(附带其它如避障、功能)
 *  作    者: 张龙(zhanglong93@sohu.com)
 *  MCU型号: IAP15W4K61S4
 *  V1.0日期: 
 *  版    本:V0.1
 *  备    注: 
 *  修改日期: 2016-06-30
 *
 **************************************************************************/
//#include	<reg52.h>
#include	"intrins.h"
#include	"STC15W4K60S4.H"
#include	"const.h"
#include	"ptype.h"
#include 	"macro.h"
#include 	"global.h"
#include 	"arch.h"
#include 	"driver.h"
#include	"main.h"
#include 	"moto.h"
#include 	"uart.h"

#include    "f_idle.h"
#include    "f_poweron.h"

u8		cnt_1ms;
u8		cnt_10ms;

//u8 xdata g_init_flag = 0;

u16 xdata g_tick;
//u16 xdata g_LRstep;	//---记录脖子左右端点的总步数

msgq_t  g_msgq;
fstack_t g_fstack;
Timer_t g_timer[CTIMER_NUM];		/** 约定g_timer[0]不用在sysProcess()中， g_timer[1]只用在sysProcess()中 **/

actionQueue_t g_actionQueue;

charQueue_t g_charTxQueue;		//only for uart1 Tx
charQueue_t g_charRxQueue;		//only for uart1 Rx

charQueue_t g_charTx3Queue;		//only for uart3 Tx
charQueue_t g_charRx3Queue;		//only for uart3 Rx

charQueue_t g_charTmpQueue;		//for Rx and process

stepMot_t 	g_stepMot_stat;

/**********************************************/
void main(void)
{
	u8	i;
	msg_t msg;
	func_t func;
	
	ADC_Init();
	timer0_Init();
	Uart1_Init();
	Uart2_Init();
	Uart3_Init();
	Uart4_Init();
	motport_init();
	
	fstack_init(&g_fstack);
	msg_init(&msg);	
	msgq_init(&g_msgq);	
	charQueueInit(&g_charTxQueue);
	charQueueInit(&g_charRxQueue);
	
	actionQueueInit(&g_actionQueue, &(g_timer[1]), CACT_TOUT, CACT_OVER);
	
	for(i = 0; i < CTIMER_NUM; i++) {
        ClrTimer(&g_timer[i]);
    }
    
	for(i = 0; i < CMOT_NUM; i++) {
        g_stepMot_stat.buf[i].stat = 0;
        g_stepMot_stat.buf[i].stop = 0;
		
        g_stepMot_stat.buf[i].scale_dst = 0;
    }
	/*** neck left/right ***/
	setNeck_LRstepCntFlag(2);		//---步进上限生效
	//setNeck_LRstepCntFlag(0);		//---步进无上限
	setNeck_LRstepLimit(12);				//---设置步进上限 (实测12 - 90度)
//	setNeck_LRstepCnt(12);			//---设置步进上限 (实测12 - 90度)
	
	/***  neck front/back  ***/
	//setNeck_FBstepCntFlag(2);		//---步进上限生效
	//setNeck_FBstep(12);				//---设置步进上限 (实测12 - 90度)
	//setNeck_FBstepCnt(12);			//---设置步进上限 (实测12 - 90度)
	
	#if	1
    SetTimer(&g_timer[0], CTIMER_1SEC, CMSG_TMR);
    SetTimer(&g_timer[2], CTIMER_10SEC, CMSG_ADC);
	#else
	//msg.msgType = CMSG_PWON;
	//msgq_in(&g_msgq, &msg);
	#endif
	
	cnt_1ms	= Timer0_Rate / 1000;	//1ms计数
	//cnt_20ms = 20;
	
	MPOWER_ON("make sure POWER_ON = 1");
	EA = 1;			//打开总中断
	while(1)
	{
		//拍脑袋动作检测
		TKInt_Detect();
		//电源按键检测
		pwrKey_Detect();
		//红外检测
		Ir_Detect();
		//其它i/o端口事件检测;
		io_detect();
		//电机状态
		motStat_detect();
		//串口发数据(to RK3188)
		uart1_Send();
		//串口发数据(to steering engine)
		uart3_send();
		
		//检查i/o事件并执行相应动作
		actionDoing(&g_actionQueue);
		
		//响应i/o事件并执行相应动作
		if(msgq_out_irq(&g_msgq, &msg) == FALSE) {     	/** 有消息吗? **/
			continue;
		}
		
		if(sysProcess(&msg) == TRUE) {   				/** 是系统消息吗? **/
			continue;
		}
		
		if(fstack_top(&g_fstack, &func) == FALSE) {    /** 当前工作状态 **/
		  /** something wrong happend, Power Down or recover it **/
		  	fstack_init(&g_fstack);
			func.func = f_idle;
			fstack_push(&g_fstack, &func);
			
			g_tick = 0;
			SetTimer_irq(&g_timer[0], CTIMER_1SEC, CMSG_TMR);
			continue;
		}
		func.func((unsigned *)&msg);
	}
}

msg_t i_msg;
u8 i;
u8 uart_Rx_Tmr = CTIMER_UART_RX + 1;
//u8 uart2_Rx_Tmr = CTIMER_UART_RX + 1;
u8 uart3_Rx_Tmr = CTIMER_UART_RX + 1;

#if	0
/*******************************************************************
 * 目标速度scale_dst到减速边界 
 *
 * 从0启动到全速转动，分频比例从15到0, 所需tick数:(15+1)*15/2
 * 从0启动到指定速度，分频比例从15到x, 所需tick数:(x+1)*x/2
 * 	...
 * 从指定速度停止，分频比例从x到15, 所需tick数: (15+x)*(15-x)/2
 *******************************************************************/
code u8 g_stepLimitBoundary_table[] = {
#define	MID2BOUNDARY(x)	(((x) + 1) * (x) / 2)
	/** Deceleration **/
	MID2BOUNDARY(15),
	MID2BOUNDARY(14),
	MID2BOUNDARY(13),
	MID2BOUNDARY(12),

	MID2BOUNDARY(11),
	MID2BOUNDARY(10),
	MID2BOUNDARY(9),
	MID2BOUNDARY(8),
	
	MID2BOUNDARY(7),
	MID2BOUNDARY(6),
	MID2BOUNDARY(5),
	MID2BOUNDARY(4),
	
	MID2BOUNDARY(3),
	MID2BOUNDARY(2),
	MID2BOUNDARY(1),
	MID2BOUNDARY(1),
};
#endif
/********************** Timer0 2kHz中断函数 ************************/
void timer0 (void) interrupt 1
{
	if(--cnt_1ms == 0)
	{
		cnt_1ms	= (Timer0_Rate / 1000);
		
		/****** ---step motor(moto NO: from 0 to CMOT_NUM - 1) ****/
	    for(i = 0; i < CMOT_NUM; i++) 
	    {
	    	if(g_stepMot_stat.buf[i].stat == 0) {			//---保持
	    		/** do nothing **/
	    	} else if(g_stepMot_stat.buf[i].stat == 1) {	//---正转
	    		//---step ascend
	    		if(g_stepMot_stat.buf[i].scale > 0) {
	    			g_stepMot_stat.buf[i].scale--;
	    		} else {
	    		    if(g_stepMot_stat.buf[i].stop == 0) { //---运行(加速状态)
						if(g_stepMot_stat.buf[i].scale_bak == g_stepMot_stat.buf[i].scale_dst) {		//---已经加速到目标速度了吗?	    				
							/** do nothing **/
						} else if(g_stepMot_stat.buf[i].scale_bak > g_stepMot_stat.buf[i].scale_dst) {	//---加速
							g_stepMot_stat.buf[i].scale_bak--;
						} else {																		//---减速
							g_stepMot_stat.buf[i].scale_bak++;	    			    
						}
	        		} else if(g_stepMot_stat.buf[i].stop == 1) {    //---停止(减速)到保持状态
	        		    if(g_stepMot_stat.buf[i].scale_bak >= 15) {
	        		        g_stepMot_stat.buf[i].stat = 0;
	        		    } else {
	        		        g_stepMot_stat.buf[i].scale_bak++;
	        		    }
	    			} else if(g_stepMot_stat.buf[i].stop == 2) {    //---停止(减速)到释放状态
	    				if(g_stepMot_stat.buf[i].scale_bak >= 15) {
	        		        g_stepMot_stat.buf[i].stat = 0;
	    					g_motStep_ALL_L[i]();
	        		    } else {
	        		        g_stepMot_stat.buf[i].scale_bak++;
	        		    }
	    			} else if(g_stepMot_stat.buf[i].stop == 3) {    //---反转
	    				if(g_stepMot_stat.buf[i].scale_bak >= 15) {
	        		        g_stepMot_stat.buf[i].stat = 2;			//---减速到最小了开始反射
	    					g_stepMot_stat.buf[i].stop = 0;			//---转化为加速状态
	        		    } else {
	        		        g_stepMot_stat.buf[i].scale_bak++;
	        		    }
	        		} else {
	    				/** do nothing **/
	    			}
	    			
	    			g_stepMot_stat.buf[i].scale = g_stepMot_stat.buf[i].scale_bak;
	    			if(g_stepMot_stat.buf[i].step >= 7) {
	    				g_stepMot_stat.buf[i].step = 0;
	    			} else {
	    				g_stepMot_stat.buf[i].step++;
	    			}
	    			
	    			if(g_stepMot_stat.buf[i].stat == 1) {
	    				/** 过程中可状态转换. 只在本状态时才转动 **/
	    				g_motStepFunc_tab[i][g_stepMot_stat.buf[i].step]();
						
						/*** 行程计数 ***/
						if(g_stepMot_stat.buf[i].stepCnt_Flag == 0) {
							/** do nothing **/
						} else if(g_stepMot_stat.buf[i].stepCnt_Flag == 1) {
							g_stepMot_stat.buf[i].stepLimit++;		//---电机转过的步数(0.9度/步)
						} else if(g_stepMot_stat.buf[i].stepCnt_Flag == 2) {
							if(g_stepMot_stat.buf[i].stepLimit == 0) {
								#if	1
								//g_stepMot_stat.buf[i].stop = 1;
								g_stepMot_stat.buf[i].stat = 0;
								#else
								i_msg.msgType = CMSG_MOTO;		/** message type **/
								i_msg.msgValue = i;				/** message value(MOTO NO.) **/
								msgq_in(&g_msgq, &i_msg);
								
								#endif
							} else {
								g_stepMot_stat.buf[i].stepLimit--;
							}
						}
						/************/
	    			}
	    		}
	    	} else if(g_stepMot_stat.buf[i].stat == 2) {	//---反转
	    		//---step decline
	    		if(g_stepMot_stat.buf[i].scale > 0) {
	    			g_stepMot_stat.buf[i].scale--;
	    		} else {
	    			if(g_stepMot_stat.buf[i].stop == 0) { //---运行(加速状态)
	        			if(g_stepMot_stat.buf[i].scale_bak == g_stepMot_stat.buf[i].scale_dst) {		//---已经加速到目标速度了吗?	    				
	        				/** do nothing **/
	        			} else if(g_stepMot_stat.buf[i].scale_bak > g_stepMot_stat.buf[i].scale_dst) {	//---加速
	        				g_stepMot_stat.buf[i].scale_bak--;
	        			} else {																		//---减速
	        			    g_stepMot_stat.buf[i].scale_bak++;	    			    
	        			}
	        		} else if(g_stepMot_stat.buf[i].stop == 1) {    //---减速到停止保持状态
	        		    if(g_stepMot_stat.buf[i].scale_bak >= 15) {
	        		        g_stepMot_stat.buf[i].stat = 0;
	        		    } else {
	        		        g_stepMot_stat.buf[i].scale_bak++;
	        		    }
	    			} else if(g_stepMot_stat.buf[i].stop == 2) {    //---减速到停止释放状态
	    				if(g_stepMot_stat.buf[i].scale_bak >= 15) {
	        		        g_stepMot_stat.buf[i].stat = 0;
	    					g_motStep_ALL_L[i]();
	        		    } else {
	        		        g_stepMot_stat.buf[i].scale_bak++;
	        		    }
	    			} else if(g_stepMot_stat.buf[i].stop == 3) {    //---反转
	    				if(g_stepMot_stat.buf[i].scale_bak >= 15) {
	        		        g_stepMot_stat.buf[i].stat = 1;			//---减速到最小了开始反转
	    					g_stepMot_stat.buf[i].stop = 0;			//---转化为加速状态
	        		    } else {
	        		        g_stepMot_stat.buf[i].scale_bak++;
	        		    }
	        		} else {
	    				/** do nothing **/
	    			}
	    			
	    			g_stepMot_stat.buf[i].scale = g_stepMot_stat.buf[i].scale_bak;
	    			if(g_stepMot_stat.buf[i].step == 0) {
	    				g_stepMot_stat.buf[i].step = 7;		
	    			} else {
	    				g_stepMot_stat.buf[i].step--;
	    			}
	    			
	    			if(g_stepMot_stat.buf[i].stat == 2) {
	    				/** 过程中可状态转换. 只在本状态时才转动 **/
	    				g_motStepFunc_tab[i][g_stepMot_stat.buf[i].step]();
						
						/***************/
						if(g_stepMot_stat.buf[i].stepCnt_Flag == 0) {
								/** do nothing **/
						} else if(g_stepMot_stat.buf[i].stepCnt_Flag == 1) {
							g_stepMot_stat.buf[i].stepLimit++;		//---电机转过的步数(的8倍)
						} else if(g_stepMot_stat.buf[i].stepCnt_Flag == 2) {
							if(g_stepMot_stat.buf[i].stepLimit == 0) {
								#if	1
								//g_stepMot_stat.buf[i].stop = 1;
								g_stepMot_stat.buf[i].stat = 0;
								#else
								i_msg.msgType = CMSG_MOTO;		/** message type **/
								i_msg.msgValue = i;				/** message value(MOTO NO.) **/
								msgq_in(&g_msgq, &i_msg);
								#endif
							} else {
								g_stepMot_stat.buf[i].stepLimit--;
							}
						}
						/***************/
	    			}
	    		}
	    	} else {
	    			/** nothing **/
	    	}
	    }
	
		/*** uart1/2 Rx *******************************/
		if(uart_Rx_Tmr < CTIMER_UART_RX) 
		{
			uart_Rx_Tmr++;
		}
		else if(uart_Rx_Tmr == CTIMER_UART_RX) 
		{
			uart_Rx_Tmr = CTIMER_UART_RX + 1;
				
			i_msg.msgType = CMSG_UARX;		/** message type **/
			//i_msg.msgValue = 1;			/** message value(no need) **/
			msgq_in(&g_msgq, &i_msg);
		} 
		
		/******* 10ms ******************/
		if(--cnt_10ms == 0)
		{
			cnt_10ms = 10;
			//B_10ms = 1;		// 10ms标志	

			/****** TK int detect **************/
			if(g_TK_int_tmr < CTIMER_TK)
			{	
				g_TK_int_tmr++;
			}
			else if(g_TK_int_tmr == CTIMER_TK) 
			{
				g_TK_int_tmr = CTIMER_TK + 1;
				
				i_msg.msgType = CMSG_TK;		/** message type **/
				//i_msg.msgValue = i;			/** message value(no need) **/
				msgq_in(&g_msgq, &i_msg);
			}	
			
			/****** PwrKey detect **************/
			if(g_pwrKey_tmr < CTIMER_PWR)
			{	
				g_pwrKey_tmr++;
			}
			else if(g_pwrKey_tmr == CTIMER_PWR) 
			{
				g_pwrKey_tmr = CTIMER_PWR + 1;
				
				i_msg.msgType = CMSG_PWRCHG;		/** message type **/
				//i_msg.msgValue = i;			/** message value(no need) **/
				msgq_in(&g_msgq, &i_msg);
			}	
			
			/****** IR detect **************/
			if(g_IR_tmr < CTIMER_IR)
			{	
				g_IR_tmr++;
			}
			else if(g_IR_tmr == CTIMER_IR) 
			{
				g_IR_tmr = CTIMER_IR + 1;
				
				i_msg.msgType = CMSG_IR;		/** message type **/
				//i_msg.msgValue = i;			/** message value(no need) **/
				msgq_in(&g_msgq, &i_msg);
			}	
			/**** IO detect *******************************/
			if(g_IO_tmr < CTIMER_IODET) 
			{
				g_IO_tmr++;
			}
			else if(g_IO_tmr == CTIMER_IODET) 
			{
				g_IO_tmr = CTIMER_IODET + 1;
				
				i_msg.msgType = CMSG_IO;		/** message type **/
				//i_msg.msgValue = 2;			/** message value(no need) **/
				msgq_in(&g_msgq, &i_msg);
			} 
			
			/**** moto detect *******************************/
			if(g_moto_tmr < CTIMER_IODET) 
			{
				g_moto_tmr++;
			}
			else if(g_moto_tmr == CTIMER_IODET) 
			{
				g_moto_tmr = CTIMER_MOTDET + 1;
				
				i_msg.msgType = CMSG_MOFLT;		/** message type **/
				//i_msg.msgValue = 2;			/** message value(no need) **/
				msgq_in(&g_msgq, &i_msg);
			} 
			/**********************************************/
			//---定时消息产生
			for(i = 0; i < CTIMER_NUM; i++) 
			{
				if(g_timer[i].tick_bak > 0) 
				{
					if(g_timer[i].tick > 0) 
					{
						g_timer[i].tick--;
					} 
					else 
					{
						g_timer[i].tick = g_timer[i].tick_bak;
                
						i_msg.msgType = g_timer[i].msgType;		/** message type **/
						i_msg.msgValue = i;						/** message value(Timer index) **/
						msgq_in(&g_msgq, &i_msg);
					}
				}
			}
		}
	}
}

/********************************************************************/
bit g_uart_Tx_busy = 0;

//串口发送接收中断函数
void Uart1_Isp(void) interrupt 4
{
	u8 ch;
    if(RI)    //收到数据
    {
        RI = 0;   //清中断请求
		ch = SBUF;
		MCHARQUE_IN(g_charRxQueue, ch);
		
		S4BUF = ch;		//!!!立即发给UART4
		
		uart_Rx_Tmr = 0;
    }
    if(TI)      //发送完一字节数据
    {
        TI = 0;
        g_uart_Tx_busy = 0;  //清正在发送标志
    }
}

//串口发送接收中断函数
void Uart2_Isp(void) interrupt 8
{
#define S2RI  0x01              //S2CON.0
#define S2TI  0x02              //S2CON.1
#define S2RB8 0x04              //S2CON.2
#define S2TB8 0x08              //S2CON.3
	
	u8	ch;
	if (S2CON & S2RI)
    {
        S2CON &= ~S2RI;         //清除S2RI位
        ch = S2BUF;             //取串口数据
        MCHARQUE_IN(g_charRxQueue, ch);
		
		S4BUF = ch;		//!!!立即发给UART4
		//S1BUF = ch;		//for debug!!!!!!!!!!!!!
		uart_Rx_Tmr = 0;
    }
    if (S2CON & S2TI)
    {
        S2CON &= ~S2TI;         //清除S2TI位
        g_uart_Tx_busy = 0;  //清正在发送标志
    }
}
/*********************************************************************/
//串口发送接收中断函数
void Uart3_Isp(void) interrupt 17
{
#define S3RI  0x01              //S3CON.0
#define S3TI  0x02              //S3CON.1
#define S3RB8 0x04              //S3CON.2
#define S3TB8 0x08              //S3CON.3

	u8 ch;
    if (S3CON & S3RI)
    {
        S3CON &= ~S3RI;         //清除S3RI位
        ch = S3BUF;             //P0显示串口数据
		MCHARQUE_IN(g_charRx3Queue, ch);
    }
    if (S3CON & S3TI)
    {
        S3CON &= ~S3TI;         //清除S3TI位
    }
	
	#if	0
	S3BUF = c;            
	while (!(S3CON & S3TI));
	S3CON &= ~S3TI;     	
	#endif
}
/*********************************************************************/
//串口发送接收中断函数
void Uart4_Isp(void) interrupt 18
{
#define S4RI  0x01              //S4CON.0
#define S4TI  0x02              //S4CON.1
#define S4RB8 0x04              //S4CON.2
#define S4TB8 0x08              //S4CON.3

	u8 ch;
    if (S4CON & S4RI)
    {
        S4CON &= ~S4RI;         //清除S4RI位
        ch = S4BUF;             //P0显示串口数据
        //P2 = (S4CON & S4RB8);   //P2.2显示校验位
    }
    if (S4CON & S4TI)
    {
        S4CON &= ~S4TI;         //清除S4TI位
        //busy = 0;               //清忙标志
    }
}
/*********************************************************************/