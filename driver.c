
//#include	<reg52.h>
#include	"STC15W4K60S4.H"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
//#include "debug.h"
#include "driver.h"
#include "arch.h"
#include "moto.h"
#include "IAP.h"
#include "main.h"

int sysProcess(msg_t *pMsg)
{
	int iRet = TRUE;
	u8 tmp;
//	u8 i;
//	static u8 P1_flag = 0;
//	msg_t msg;
	
	switch(pMsg->msgType)
	{
		case CACT_TOUT:			/** 一个动作阶段完成 **/
			actProcess(&g_actionQueue);
			break;
		
		case CMSG_ADC:
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_HEAD);
			charQueueIn_irq(&g_charTxQueue, 3);
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_ADCCOMM);
			tmp = ADC_get();
		#if	0
		    /**************************************************
			 * 与分压电阻有关(33K/10K, 按1/4计算, 256/4 = 64)
			 * (7V/8.4V = 0.836)
			 **************************************************/
			//tmp = (tmp < 214)? 214:tmp;
			//tmp = (tmp - 214)/6;
		
			tmp = (tmp < 53)? 53:tmp;
			tmp = (tmp - 53)/2;
		#endif
			charQueueIn_irq(&g_charTxQueue, tmp);
			charQueueIn_irq(&g_charTxQueue, 0);
			break;
		
		case CMSG_TMR:			/** tick **/
			g_tick++;
		
			//POWER_ON = !POWER_ON;
			/*****************************************************/
			#if	0	/** 注意eeprom/flash擦写寿命10W次 **/
			IapEraseSector(CIAP_ADDRESS);    //扇区擦除
			for (i = 0; i < 8; i++)           //编程512字节
			{
				IapProgramByte(CIAP_ADDRESS + i, (i << 1));
			}
			for (i = 0; i < 8; i++)           //校验512字节
			{
				tmp = IapReadByte(CIAP_ADDRESS + i);
				charQueueIn_irq(&g_charTxQueue, tmp);
			}
			#endif
			/******************************************************/
			break;
		
		case CMSG_UARX:			/** uart received data **/
			charQueueMove_irq(&g_charRxQueue, &g_charTmpQueue);
			phrase_command(&g_charTmpQueue);
		
			#if	0
			P1 = cnt++;	//?????????????????????????????????????		
			if((cnt & 0x07) == 0x07) {
				setHand_leftForward();
			} else if((cnt & 0x07) == 0x05){
				setHand_leftStop(1);
			} else if((cnt & 0x07) == 0x03){
				setHand_leftBackward();
			} else if((cnt & 0x07) == 0x01){
				setHand_leftStop(1);
			}
			#endif
			break;

		case CMSG_PWRCHG:
			//---检测到障碍
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_HEAD);
			charQueueIn_irq(&g_charTxQueue, 3);
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_SLEEPCOMM);
			tmp = pwrKey_Detect();
			//charQueueIn_irq(&g_charTxQueue, (tmp & 1));
			charQueueIn_irq(&g_charTxQueue, !(!tmp));
			charQueueIn_irq(&g_charTxQueue, 0);	
			break;
		
		case CMSG_TK:
			//---检测到拍脑袋
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_HEAD);
			charQueueIn_irq(&g_charTxQueue, 3);
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_TKCOMM);
			tmp = TKInt_Detect();
			//charQueueIn_irq(&g_charTxQueue, (tmp & 1));
			charQueueIn_irq(&g_charTxQueue, !(!tmp));
			charQueueIn_irq(&g_charTxQueue, 0);	
			break;
		
		case CMSG_IR:
			//---检测到障碍
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_HEAD);
			charQueueIn_irq(&g_charTxQueue, 3);
			charQueueIn_irq(&g_charTxQueue, CPROTOCAL_IRCOMM);
			//tmp = MIR_DET("4 IR pin stat");
			tmp = Ir_Detect();
			charQueueIn_irq(&g_charTxQueue, tmp);
			charQueueIn_irq(&g_charTxQueue, 0);
			break;
		
		case CMSG_IO:
			//---检测到IO事件
		#if	1
			tmp = io_detect();
			if(tmp & (1 << 2)) {		//---左边界
				setNeck_LRstop(1);
			} else if(tmp & (1 << 1)) {	//---右边界
				setNeck_LRstop(1);
			//} else if(tmp & 1) {		//---电源
			} else {
				#if	0
				//---检测到电源开关
				charQueueIn_irq(&g_charTxQueue, CPROTOCAL_HEAD);
				charQueueIn_irq(&g_charTxQueue, 3);
				charQueueIn_irq(&g_charTxQueue, CPROTOCAL_SLEEPCOMM);
				//tmp = io_detect();
				charQueueIn_irq(&g_charTxQueue, (tmp & 1));
				charQueueIn_irq(&g_charTxQueue, 0);
				#endif
			}
		#endif
			break;
		
		case CMSG_MOTO:
			//---电机走完指定的步数
			setMoto_stop(((msg_t *)pMsg)->msgValue);
			break;
		
		case CACT_OVER:			/** 动作完成 **/
			actionQueueInit(&g_actionQueue, &(g_timer[1]), CACT_TOUT, CACT_OVER);
			break;
		
		default:
			/** Can't process the msg here **/
			iRet = FALSE;
			break;
	}
	
	return iRet;
}

/*******************************************************************************
 * value_inc()/value_dec()
 * 将指定的变量在[_max, _min]区间内加/减1. 
 *******************************************************************************/
#if	0
u8 value_inc(u8 _value, u8 _max, u8 _min)
{
	if(_value >= _max) {
		_value = _min;
	} else {
		_value += 1;
	}
	
	return	_value;
}

u8 value_dec(u8 _value, u8 _max, u8 _min)
{
	if(_value <= _min) {
		_value = _max;
	} else {
		_value -= 1;
	}
	
	return	_value;
}
#endif

 /******************************************************************************
  * function: phrase_command
  * Description: get received data from FIFO and phrase
  * input: src - pointer of FIFO
  * output: arr - the data get from FIFO
  * return: <= 12 the length of data get from FIFO
  * Get all of the data in the FIFO
  * 
  * make sure
  *******************************************************************************/
u8 phrase_command(charQueue_t *src) 
{
    u8 i = 255;

	u8 head;
	u8 len;
	u8 comm[5];
	while(charQueueOut(src, &head) == TRUE) {
        if((head == CPROTOCAL_HEAD) && (i == 255)) {		/** 找到命令头(第一个0x5a) **/
    		i = 0;
            break;
        }
    }
	if(i == 0) {	//---如果找到了命令头，就继续找命令内容
		charQueueOut(src, &len);	//---command length
		
		while((len > 0) && (i < 5)) {	//---command context
			charQueueOut(src, &comm[i]);
			i++;
		}
		
		switch(comm[0])
		{
		case CPROTOCAL_MOTOCOMM:			/** MOTO **/
			/******************************/
			#if	0
			charQueueIn_irq(&g_charTxQueue, comm[1]);
			charQueueIn_irq(&g_charTxQueue, comm[2]);
			charQueueIn_irq(&g_charTxQueue, comm[3]);
			#endif
			/******************************/
			if(comm[1] <= 0x36) {
				//IR_power_on();		//---开启障碍检测
				if(len >= 3) {
					g_setSpeedTable[comm[1]](comm[2]);		//---速度
					if(len >= 4) {
						g_setStepLimitTable[comm[1]](comm[3]);	//---角度(也就是前进距离)
					}
				}
				g_partActionTable[comm[1]]();
			}
			
			break;
		
		case CPROTOCAL_LEDCOMM:			/** LED **/
			/** do something here **/
			break;
		
		case CPROTOCAL_IRCOMM:			/** uart received data **/
			/** do nothing **/
			break;
		
		case CPROTOCAL_SLEEPCOMM:			/** uart received data **/
			/** power on/off **/
			if(comm[1] != 0) {
				POWER_ON = 1;
			} else {
				POWER_ON = 0;
			}
			break;
		
		default:
			break;
		}
	}
    return	0;		/** 没有收到正常数据 **/
}

/*************************************************************************/

/*************************************************************************
 * 电源按键i/o检测
 *************************************************************************/
u8	g_pwrKey_tmr = CTIMER_PWR + 1;
#if	1
u8 pwrKey_Detect(void)
{	
	#if	0
	static u8 io_stat = 0;	
	static u8 stat_last = 0;	//---上次状态
	u8	stat = 0;
	
	//---(高有效)电源键按下
	if(POWER_KEY == 1) {stat |= (1);} else {stat &= ~(1);}

	if(io_stat == 0x0) {					/** S1 - 稳态 **/
		if((stat ^ stat_last) != 0) {
			g_pwrKey_tmr = 0;
			io_stat = (0x01);
		} else {
			/** do nothing **/
		}
	} else { // if(io_stat == 0x01) {		/** S2 - 变化确认中 **/
		if((stat ^ stat_last) != 0) {
			//if(g_pwrKey_tmr >= CTIMER_PWR) {
			if(g_pwrKey_tmr > CTIMER_PWR) {
				io_stat = (0x0);	
				stat_last = stat;
			}
		} else {
			io_stat = 0x0;
			g_pwrKey_tmr = CTIMER_PWR + 1;
		}
	}

	return	stat_last;
#else
	
	//---(高有效)电源键按下
	if(POWER_KEY == 1) {PWR_CRL = 1;} else {PWR_CRL = 0;}
	return	0;
#endif
}
#endif


/*************************************************************************
 * TK按键i/o检测
 *************************************************************************/
u8	g_TK_int_tmr = CTIMER_TK + 1;
#if	1
u8 TKInt_Detect(void)
{	
	#if	1
	static u8 io_stat = 0;	
	static u8 stat_last = 0;	//---上次状态
	u8	stat = 0;
	
	//---(高有效)电源键按下
	if(TK_INT == 1) {stat |= (1);} else {stat &= ~(1);}

	if(io_stat == 0x0) {					/** S1 - 稳态 **/
		if((stat ^ stat_last) != 0) {
			g_TK_int_tmr = 0;
			io_stat = (0x01);
		} else {
			/** do nothing **/
		}
	} else { // if(io_stat == 0x01) {		/** S2 - 变化确认中 **/
		if((stat ^ stat_last) != 0) {
			if(g_TK_int_tmr > CTIMER_TK) {
				io_stat = (0x0);
				stat_last = stat;
			}
		} else {
			io_stat = 0x0;
			g_TK_int_tmr = CTIMER_TK + 1;
		}
	}

	return	stat_last;
#endif
}
#endif



/*************************************************************************
 * 红外信号i/o检测
 *************************************************************************/
u8	g_IR_tmr = CTIMER_IR + 1;
u8 Ir_Detect(void)
{	
	static u8 io_stat = 0;	
	static u8 stat_last = 0;	//---上次状态	
	u8 stat;
	
	/** 
	 * 只在左右脚动作的时候才开障碍检测
	 **/
	
	if((g_stepMot_stat.buf[0].stat == 0) && (g_stepMot_stat.buf[1].stat == 0)) {
		MIR_POWER_OFF("左右脚电机都停止");
	} else {
		MIR_POWER_ON("左右脚电机有转动");
	}
	
	//---红外避障(前后为高、下方为低)
	if(IR1 == 1) {stat |= (1 << 4);} else {stat &= ~(1 << 4);}
	if(IR2 == 1) {stat |= (1 << 5);} else {stat &= ~(1 << 5);}
	//---红外避障(前后为高、下方为低)	
	if(IR3 == 0) {stat |= (1 << 6);} else {stat &= ~(1 << 6);}
	if(IR4 == 0) {stat |= (1 << 7);} else {stat &= ~(1 << 7);}

	#if	1
	if(io_stat == 0x0) {					/** S1 - 稳态 **/
		if((stat ^ stat_last) != 0) {
			g_IR_tmr = 0;
			io_stat = (0x01);
		} else {
			/** do nothing **/
		}
	} else { // if(io_stat == 0x01) {		/** S2 - 变化确认中 **/
		if((stat ^ stat_last) != 0) {
			if(g_IR_tmr >= CTIMER_IR) {
				io_stat = (0x0);	
				stat_last = stat;
			}
		} else {
			io_stat = 0x0;
			g_IR_tmr = CTIMER_IR + 1;
		}
	}
	#endif

	//return	stat;
	return	stat_last;
}

/*************************************************************************
 * i/o状态变化检测
 * 
 * S1(稳态) <--> S2(...)
 *
 * 电源按键
 * 限位开关
 * 其它状态开关
 *************************************************************************/

u8	g_IO_tmr = CTIMER_IODET + 1;
u8 io_detect(void)
{
	static u8 io_stat = 0;	
	static u8 stat_last = 0;	//---上次状态
	u8	stat = 0;
	
	//---(高有效)电源键按下
	if(POWER_KEY == 1) {stat |= (1);} else {stat &= ~(1);}
	//---(低有效)向右限位开关
	if(R_SW == 0) {stat |= (1 << 1);} else {stat &= ~(1 << 1);}
	//---(低有效)向左限位开关
	if(L_SW == 0) {stat |= (1 << 2);} else {stat &= ~(1 << 2);}
	//---(高有效)TK
	if(TK_INT == 0) {stat |= (1 << 3);} else {stat &= ~(1 << 3);}
	//---(电池)
	//if(BAT_DET == 0) {stat |= (1 << 4);} else {stat &= ~(1 << 4);}	//---电量A/D检测, 不读端口电平
	//---(高有效)充电检测
	if(CHG_DET == 0) {stat |= (1 << 5);} else {stat &= ~(1 << 5);}
	//---(低有效)电池充满
	if(CHG_DONE == 0) {stat |= (1 << 6);} else {stat &= ~(1 << 6);}
	
	#if	1
	if(io_stat == 0x0) {				/** S1 **/
		if((stat ^ stat_last) != 0) {
			g_IO_tmr = 0;
			io_stat = (0x01);
		} else {
			/** do nothing **/
		}
	} else { //if(io_stat == 0x01) {		/** S2 **/
		if((stat ^ stat_last) != 0) {
			if(g_IO_tmr >= CTIMER_IODET) {
				io_stat = (0x0);	
				stat_last = stat;
			}
		} else {
			io_stat = 0x0;
			g_IO_tmr = CTIMER_IODET + 1;
		}
	}
	#endif
	
	return	stat;
}

/************************************************************************/

u8	g_moto_tmr = CTIMER_IODET + 1;
u8 motStat_detect(void)
{
	static u8 io_stat = 0;	
	static u8 stat_last = 0;	//---上次状态
	u8	stat = 0;
	
	if(M1_I_DET == 0) {stat |= (1 << 1);} else {stat &= ~(1 << 1);}	//---电机驱动异常。低有效
	if(M2_I_DET == 0) {stat |= (1 << 2);} else {stat &= ~(1 << 2);}
	if(M3_I_DET == 0) {stat |= (1 << 3);} else {stat &= ~(1 << 3);}
	if(M4_I_DET == 0) {stat |= (1 << 4);} else {stat &= ~(1 << 4);}
	if(M5_I_DET == 0) {stat |= (1 << 5);} else {stat &= ~(1 << 5);}
	if(M6_I_DET == 0) {stat |= (1 << 6);} else {stat &= ~(1 << 6);}

	#if	1
	if(io_stat == 0x0) {					/** S1 **/
		if((stat ^ stat_last) != 0) {
			g_moto_tmr = 0;
			io_stat = (0x01);
		} else {
			/** do nothing **/
		}
	} else { 	//if(io_stat == 0x01) {		/** S2 **/
		if((stat ^ stat_last) != 0) {
			if(g_moto_tmr >= CTIMER_IODET) {
				io_stat = (0x0);	
				stat_last = stat;
			}
		} else {
			io_stat = 0x0;
			g_moto_tmr = CTIMER_IODET + 1;
		}
	}
	#endif

	return	stat;
}

/*************************************************************************/
#define	CADC_POWER	0x80
#define	CADC_SPEED	(0 << 5)
#define	CADC_START	(1 << 3)
#define	CADC_REDY	(1 << 4)
#define	CADC_CH	0x05

void	ADC_Init(void)
{
	//P1M0 = 0x20;                 //0010 0000
    //P1M1 = 0x20;                 //0010 0000 //设置P1.5为AD转换输入模式
	P1M0 |= (1 << 5);                 //0010 0000
    P1M1 |= (1 << 5);                 //0010 0000 //设置P1.5为AD转换输入模式
	P1ASF	|=	(1 << 5);
	P1 |= (1 << 5);
	
	CLK_DIV     &= ~(1 << 5);  //CLK_DIV的D5位为0，转换结果高8位存ADC_RES,低2位存ADC_RESL的低两位；
	//CLK_DIV     |= (1 << 5);  //CLK_DIV的D5位为1，转换结果低8位存ADC_RESL,高2位存ADC_RES的低两位；
	
	ADC_RES = 0;
	ADC_CONTR	=	(CADC_POWER | CADC_SPEED | CADC_START | CADC_CH);
}

/** 取AD后的高8位, 忽略低2位 **/
u8	ADC_get(void)
{
	u8	adcDataH = 0;
	if(ADC_CONTR & CADC_REDY)
	{
		ADC_CONTR &= ~CADC_REDY;
		adcDataH = ADC_RES;
		
		ADC_CONTR	=	(CADC_POWER | CADC_SPEED | CADC_START | CADC_CH);
		
		return	adcDataH;
	}
	return	adcDataH;
}
/*************************************************************************/

void timer0_Init(void)
{
	//EA = 0; 		//暂时关闭中断
	ET0 = 0;		//Timer0 Interrupt Enable
	AUXR |=  (1 << 7);	// Timer0 set as 1T mode(valid for 15w4k61s4)
	TMOD &= ~(1 << 2);	// Timer0 set as Timer
	TMOD &= ~0x03;		// Timer0 set as 16 bits Auto Reload
	//TMOD |= 0x01;
	
	TH0 = ((Timer0_Reload >> 8) & 0xff);	//Timer0 Load
	TL0 = (Timer0_Reload & 0xff);
	//TH0 = 0xEA;	//Timer0 Load(0xfe33:实测最接近数据2K)
	//TL0 = 0x67;
	
	ET0 = 1;		//Timer0 Interrupt Enable
	PT0 = 1;		//高优先级
	TR0 = 1;		//Timer0 Run
	//EA = 1;			//打开总中断
}

/*************************************************************************/
void motport_init(void)
{
	//---moto1
    P1M0 &= ~0x1C;
    P1M1 &= ~0x1C;	
    P4M0 &= ~0x80;
    P4M1 &= ~0x80;
	
	//---moto2
    P6M0 &= ~0x0F;
    P6M1 &= ~0x0F;
	
	//---moto3
    P2M0 &= ~0xF0;
    P2M1 &= ~0xF0;
	
	//---moto4
    P7M0 &= ~0xF0;
    P7M1 &= ~0xF0;
	
	//---moto5
    P0M0 &= ~0x30;
    P0M1 &= ~0x30;
    P5M0 &= ~0x0C;
    P5M1 &= ~0x0C;
	
	//---moto6
    P4M0 &= ~0x0E;
    P4M1 &= ~0x0E;
    P7M0 &= ~0x08;
    P7M1 &= ~0x08;
	/********************************/
	//---power on(P7.2)
	#if	1
	P7M0 |= 0x04;
    P7M1 &= ~0x04;	//---高阻输入
	#else
	P7M0 &= ~0x04;	//---准双向
    P7M1 &= ~0x04;
	#endif
	P7 |= 0x04;		//---默认上电高电平
	/********************************/
	//---pwr_crl(P3.7)
	#if	1
	P3M0 |= 0x80;
    P3M1 &= ~0x80;	//---强推挽输出
	#else
	P3M0 &= ~0x80;	//---准双向
    P3M1 &= ~0x80;
	#endif
	P3 &= ~0x80;		//---默认上电低电平
	/********************************/
	//---power key(P7.1)
	#if	1
	P7M0 |= 0x02;	//---开漏
    P7M1 |= 0x02;
	#else
	P7M0 &= ~0x02;
    P7M1 |= 0x02;	//---强推挽输出
	#endif
	//P7 |= 0x02;		//---默认上电高电平
	/********************************/
	//---Ir_Power
	P3M0 |= 0x30;
    P3M1 &= ~0x30;	//---强推挽输出
	
	P3 |= 0x20;		//---默认上电高电平
	P3 &= ~0x10;	//---默认上电低电平
	
	/********************************/
	//---TK int(P2.3)
	P2M0 |= 0x08;
    P2M1 |= 0x08;	//---开漏
	/********************************/
	//---Debug
	P5M0 |= 0x01;
    P5M1 &= ~0x01;	//---强推挽输出
	
	P5 |= 0x01;		//---默认上电高电平
	//P5 &= ~0x01;	//---默认上电低电平
	/********************************/
}

/*************************************************************************/
#if	0
/** 红外避障电源接通 **/
void IR_power_on(void)
{
	IR_PWR_CRL = 0;
	IR_CRL = 1;
}
/** 红外避障电源接通断开 **/
void IR_power_off(void)
{
	IR_PWR_CRL = 1;
	IR_CRL = 0;
}
#endif
/*************************************************************************/
