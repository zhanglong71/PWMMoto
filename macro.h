#ifndef __MACRO_H__
#define __MACRO_H__

/** process charQueue_t **/
#if	0
#define	MCHARQUE_INIT(q) do{\
						q->tail = q->head = 0;\
								}while(0);

#define	MCHARQUE_IN(q, ch) do{\
								q->buf[q->tail]      = ch;\
								q->tail = ((q->tail + 1) % CHARQUEUESIZE);\
								}while(0);

#define	MCHARQUE_OUT(q, ch) do{\
								ch = q->buf[q->head];\
								q->head = ((q->head + 1) % CHARQUEUESIZE);\
								}while(0);

#else
#define	MCHARQUE_INIT(q) do{\
						q.tail = q.head = 0;\
								}while(0);

#define	MCHARQUE_IN(q, ch) do{\
								q.buf[q.tail]      = ch;\
								q.tail = ((q.tail + 1) % CHARQUEUESIZE);\
								}while(0);


#define	MCHARQUE_OUT(q, ch) do{\
								ch = q.buf[q.head];\
								q.head = ((q.head + 1) % CHARQUEUESIZE);\
								}while(0);
#endif
/************************************************************************/
#define	MPWMTMR_SET(id, val) do {g_pwm.buf[id] = val;} while(0);
/************************************************************************/
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0])) 
/************************************************************************/


#if	1
//------nSleep
sbit	MOT_SLEEP	=	P2^0;
#define	MMOT_SLEEP(x)	do{MOT_SLEEP = !(x);}while(0)
//------左轮
sbit	MOT1_A1	=	P4^7;
sbit	MOT1_A2	=	P1^2;
sbit	MOT1_B1	=	P1^3;
sbit	MOT1_B2	=	P1^4;
//---
sbit	M1_I_DET	=	P0^6;
//------右轮
sbit	MOT2_A1	=	P6^0;
sbit	MOT2_A2	=	P6^1;
sbit	MOT2_B1	=	P6^2;
sbit	MOT2_B2	=	P6^3;
//---
sbit	M2_I_DET	=	P0^7;
//---左手
sbit	MOT3_A1	=	P2^4;
sbit	MOT3_A2	=	P2^5;
sbit	MOT3_B1	=	P2^6;
sbit	MOT3_B2	=	P2^7;
//---
sbit	M3_I_DET	=	P4^6;
//---右手
sbit	MOT4_A1	=	P7^4;
sbit	MOT4_A2	=	P7^5;
sbit	MOT4_B1	=	P7^6;
sbit	MOT4_B2	=	P7^7;
//---
sbit	M4_I_DET	=	P4^5;

//---摇头
sbit	MOT5_A1	=	P5^3;
sbit	MOT5_A2	=	P0^5;
sbit	MOT5_B1	=	P5^2;
sbit	MOT5_B2	=	P0^4;
//---
sbit	M5_I_DET	=	P2^2;

//---点头
sbit	MOT6_A1	=	P4^3;
sbit	MOT6_A2	=	P4^2;
sbit	MOT6_B1	=	P4^1;
sbit	MOT6_B2	=	P7^3;
//---
sbit	M6_I_DET	=	P2^1;
//---
#endif
/*************************************************************************/
//---限位开关
sbit	R_SW	=	P3^2;
sbit	L_SW	=	P3^3;
/*************************************************************************/
//---Power
sbit	POWER_KEY	=	P7^1;		//---detect the power key(I)
sbit	POWER_ON	=	P7^2;		//---control the power on/off(O)
sbit	RTC_WU	=	P7^0;			//---使用场景不明?????????????????????????????????????????????????
sbit	PWR_CRL	=	P3^7;			//---RK3188唤醒脚(使用场景: 跟随POWER_KEY)

/*************************************************************************/
sbit	T4	=	P5^0;			//---RK3188唤醒脚(使用场景不明????????????????????????????????????)
#define	DDEBUG(x)	do{T4 ^= 1;}while(0)	//?????????????????????????????????????????????????????
/*************************************************************************/
#define	MPOWER_ON(x)	do{POWER_ON = 1;}while(POWER_ON != 1)	//---make sure power_on = 1
/*************************************************************************/
#if	0
//--full step
#define	MMOT_STEP1(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 1; MOT##x##_B1 = 0; MOT##x##_B2 = 1;}while(0)
#define	MMOT_STEP2(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 1; MOT##x##_B1 = 1; MOT##x##_B2 = 0;}while(0)
#define	MMOT_STEP3(x)	do{MOT##x##_A1 = 1; MOT##x##_A2 = 0; MOT##x##_B1 = 0; MOT##x##_B2 = 1;}while(0)
#define	MMOT_STEP4(x)	do{MOT##x##_A1 = 1; MOT##x##_A2 = 0; MOT##x##_B1 = 1; MOT##x##_B2 = 0;}while(0)

#else
//---half step
#define	MMOT_STEP1(x)	do{MOT##x##_A1 = 1; MOT##x##_A2 = 0; MOT##x##_B1 = 1; MOT##x##_B2 = 0;}while(0)
#define	MMOT_STEP2(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 0; MOT##x##_B1 = 1; MOT##x##_B2 = 0;}while(0)
#define	MMOT_STEP3(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 1; MOT##x##_B1 = 1; MOT##x##_B2 = 0;}while(0)
#define	MMOT_STEP4(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 1; MOT##x##_B1 = 0; MOT##x##_B2 = 0;}while(0)
#define	MMOT_STEP5(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 1; MOT##x##_B1 = 0; MOT##x##_B2 = 1;}while(0)
#define	MMOT_STEP6(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 0; MOT##x##_B1 = 0; MOT##x##_B2 = 1;}while(0)
#define	MMOT_STEP7(x)	do{MOT##x##_A1 = 1; MOT##x##_A2 = 0; MOT##x##_B1 = 0; MOT##x##_B2 = 1;}while(0)
#define	MMOT_STEP8(x)	do{MOT##x##_A1 = 1; MOT##x##_A2 = 0; MOT##x##_B1 = 0; MOT##x##_B2 = 0;}while(0)

#endif

#define	MMOT_STEP_ALL_L(x)	do{MOT##x##_A1 = 0; MOT##x##_A2 = 0; MOT##x##_B1 = 0; MOT##x##_B2 = 0;}while(0)
/*************************************************************************/
#define	MMOT_STEP(x, y)	do{MMOT_STEP##y(x);}while(0)
/*************************************************************************/
#define MMOT_SPEED(x, y)	do{\
			g_stepMot_stat.buf[x].scale_dst = y;\
			g_stepMot_stat.buf[x].scale = y;\
							}while(0)
/*************************************************************************/
#if	0
#define MSETMOT_STEPCNT(x, y)		do{\
			g_stepMot_stat.buf[x].stepCnt = y;\
							}while(0)

#define MGETMOT_STEPCNT(x)	(g_stepMot_stat.buf[x].stepCnt)
#endif
/*************************************************************************/
#define MSETMOT_STEPFLAG(x, y)		do{\
			g_stepMot_stat.buf[x].stepCnt_Flag = y;\
							}while(0)

//#define MGETMOT_STEPFLAG(x)	(g_stepMot_stat.buf[x].stapCnt_Flag)
/*************************************************************************/
#define	MID2STEP(x)	((x / 3) * 50 + g_stepLimitScale_table[x % 3])
/*************************************************************************/
	/** 红外 **/
sbit	IR_CRL	=	P3^4;		//---输出控制
sbit	IR_PWR_CRL	=	P3^5;	//---电源控制
#define	MIR_DET(x) ((P6 & 0xF0) != 0)

sbit	IR1	=	P6^4;	
sbit	IR2	=	P6^5;
sbit	IR3	=	P6^6;
sbit	IR4	=	P6^7;

#define	MIR_POWER_ON(x)	do{IR_PWR_CRL = 0; IR_CRL = 1;}while(0)
#define	MIR_POWER_OFF(x)	do{IR_PWR_CRL = 1; IR_CRL = 0;}while(0)
/*************************************************************************/
	/** 电池 **/
sbit	BAT_DET		=	P1^5;		//---电量检测(A/D)
sbit	CHG_DET		=	P3^6;		//---充电检测
sbit	CHG_DONE	=	P5^1;		//---充电完成
/*************************************************************************/
//---拍脑袋
sbit	TK_INT	=	P2^3;
/*************************************************************************/

/*************************************************************************/
#endif
