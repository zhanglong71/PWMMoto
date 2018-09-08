#ifndef __GLOBAL_H__
#define __GLOBAL_H__

extern u16 xdata g_tick;
//extern u16 xdata g_LRstep;
//extern u8 xdata g_init_flag;

extern	msgq_t  g_msgq;
extern	fstack_t g_fstack;
extern	Timer_t g_timer[CTIMER_NUM];

extern actionQueue_t g_actionQueue;

//extern charQueue_t g_charQueue;
extern charQueue_t g_charTxQueue;
extern charQueue_t g_charRxQueue;
extern charQueue_t g_charTmpQueue;		//for Rx and process

extern	u8	g_pwrKey_tmr;
extern	u8	g_TK_int_tmr;
extern 	u8	g_IR_tmr;
extern 	u8	g_KEY_tmr;
extern	u8	g_IO_tmr;
extern	u8	g_moto_tmr;

extern bit g_uart_Tx_busy;
extern code paction_t_0 g_motStepFunc_tab[][8];
extern code paction_t_0 g_motStep_ALL_L[];
extern stepMot_t g_stepMot_stat;

extern	code paction_t_0 g_partActionTable[];
extern	code paction_t_1 g_setSpeedTable[];
extern	code paction_t_1 g_setStepLimitTable[];

#endif