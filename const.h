#ifndef __CONST_H__
#define __CONST_H__
/**************************************************************************/
#define MAIN_Fosc		11059200UL	//定义主时钟
//#define	Timer0_Rate		25000UL		//中断频率
#define	Timer0_Rate		2000UL		//中断频率
#define	Baud_Rate		9600UL		//uart波特率

#define	Timer0_Reload	(65536UL -(MAIN_Fosc / Timer0_Rate))	//Timer 0 重装值

/**************************************************************************/
#define CTIMER_NUM	3       /** the number of timer(0 - timer tick, 1 - for actionMOT, 2 - for ADC) **/
/**************************************************************************/
#define	TRUE	1
#define	FALSE	0
/**************************************************************************/
#define	CTIMER_10MS		(1)
#define	CTIMER_20MS		(2 * CTIMER_10MS)
#define	CTIMER_100MS	(10 * CTIMER_10MS)

#define	CTIMER_1SEC		(10 * CTIMER_100MS)

#define	CTIMER_3SEC		(3 * CTIMER_1SEC)
#define	CTIMER_10SEC	(10 * CTIMER_1SEC)
/**************************************************************************/

//#define		CPWM_DUTY_MAX	100	// 0~100	PWM周期, 最大100
//#define		PWM_DUTY_MAX	250	// 0~255	PWM周期, 最大255
/**************************************************************************/
#define CTIMER_UART_RX (7)
/**************************************************************************/
#define CTIMER_IR 	(1)
#define CTIMER_PWR 	(1)
#define CTIMER_TK 	(1)
#define CTIMER_IODET 	(1)
#define CTIMER_MOTDET 	(1)
/**************************************************************************/
#define	CIAP_ADDRESS	0xF000
/**************************************************************************/
//--- for protocal
#define	CPROTOCAL_HEAD	(0x5A)
//----------------------------
#define	CPROTOCAL_MOTOCOMM	(1)
				#define	CPROTOCAL_MOTOCOMM_FORWARD	(1)
				#define	CPROTOCAL_MOTOCOMM_BACKWARD	(2)
				#define	CPROTOCAL_MOTOCOMM_TURNLEFT	(3)
				#define	CPROTOCAL_MOTOCOMM_TURNRIGHT	(4)
				#define	CPROTOCAL_MOTOCOMM_FOOTSTOP	(5)
				
				#define	CPROTOCAL_MOTOCOMM_LEFTHAND_FORWARD		(8)
				#define	CPROTOCAL_MOTOCOMM_LEFTHAND_BACKWARD	(9)
				#define	CPROTOCAL_MOTOCOMM_LEFTHAND_STOP		(10)
				
				#define	CPROTOCAL_MOTOCOMM_RIGHTHAND_FORWARD	(16)
				#define	CPROTOCAL_MOTOCOMM_RIGHTHAND_BACKWARD	(17)
				#define	CPROTOCAL_MOTOCOMM_RIGHTHAND_STOP		(18)
				
				#define	CPROTOCAL_MOTOCOMM_NECK_LEFT		(24)
				#define	CPROTOCAL_MOTOCOMM_NECK_RIGHT		(25)	
				#define	CPROTOCAL_MOTOCOMM_NECK_LRSTOP		(26)
				
				#define	CPROTOCAL_MOTOCOMM_NECK_FORWARD		(32)
				#define	CPROTOCAL_MOTOCOMM_NECK_BACKWARD	(33)	
				#define	CPROTOCAL_MOTOCOMM_NECK_FBSTOP		(34)
#define	CPROTOCAL_MOTORESP	(2)
//-----------------------------
#define	CPROTOCAL_LEDCOMM	(3)
				#define	CPROTOCAL_LEDCOMM_TALK		(1)
				#define	CPROTOCAL_LEDCOMM_BLINK		(2)
				#define	CPROTOCAL_LEDCOMM_SHAKE		(3)
#define	CPROTOCAL_LEDRESP	(4)
//-----------------------------
#define	CPROTOCAL_IRCOMM	(5)		//---红外壁障
#define	CPROTOCAL_IRRESP	(6)
//-----------------------------
#define	CPROTOCAL_SLEEPCOMM	(7)		//---休眠按键
#define	CPROTOCAL_SLEEPRESP	(8)
//-----------------------------
#define	CPROTOCAL_ADCCOMM	(9)		//---ADC电量检测
#define	CPROTOCAL_ADCRESP	(10)	//---ADC电量检测
//-----------------------------
#define	CPROTOCAL_TKCOMM	(0x0b)	//---TK动作检测
#define	CPROTOCAL_TKRESP	(0x0c)	//---TK动作检测
/**************************************************************************/
#endif