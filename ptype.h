#ifndef __CTYPE_H__
#define __CTYPE_H__


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long	u32;

typedef char s8;
typedef short s16;
typedef long	s32;

typedef	void	(*paction_t_0)(void);
typedef	void	(*paction_t_1)(u8 arg);

typedef	int	(*pfunc_t)(void *arg);

typedef struct func_s {
    pfunc_t		func;       /** function **/
    void  *arg;    	/** argument **/
} xdata func_t;

typedef struct func_stack{
	u8		top;
		#define	STACKSIZE	8
	func_t		func[STACKSIZE]; 
} xdata fstack_t;

typedef enum {
	CMSG_NONE,
	CMSG_PWON,
	CMSG_INIT,
	CMSG_TMR,
	CMSG_ADC,
	CMSG_TK,	//---
	CMSG_IO,	//çŠ¶æ€ç«¯å£æœ‰å˜åŒ–(æŒ‰é”®ã€é™ä½å¼€å…³)
	
	CACT_TOUT,	//phrase over
	CACT_OVER,	//all over
	
	CMSG_UARX,	//uart received
	CMSG_UATX,	//uart transported
	
	CMSG_PWRCHG,	//---æœ‰å˜åŒ–
	CMSG_IR,	//çº¢å¤–ä¿¡å·å˜åŒ–
	CMSG_MOTO,	//ç”µæœºå¼‚å¸¸
	CMSG_MOFLT,	//ç”µæœºå¼‚å¸¸
}msgType_t;

typedef struct msg_s {
	msgType_t msgType;
	
	u8	msgValue;
}xdata msg_t;

typedef struct msg_queue{
	u8	head;
	u8	tail;
	
		#define	QUEUESIZE	8		/** Ğ»Ï¢×“ÂÕ³Ğ¡ **/
	msg_t msg[QUEUESIZE];
}xdata msgq_t;

typedef struct Timer_s {
    u16 tick_bak;
    u16 tick;
    msgType_t msgType;                      /** the type of msg when timeout **/
    //unsigned int count;                   /** Is it necessary ? **/
}xdata Timer_t;
//}idata Timer_t;
//} Timer_t; 

typedef struct charQueue_s {
  
    u8	head:4;
	u8	tail:4;
		//u8 flag;
        #define CHARQUEUESIZE 8
    u8 buf[CHARQUEUESIZE];     /** 8 bytes **/
}xdata charQueue_t;
//}idata charQueue_t;

typedef struct action_s {
	/*****************
	 * MOT1-ON
	 * MOT1-OFF
	 * MOT1-REV
	 *
	 * MOT2-ON
	 * MOT2-OFF
	 * MOT2-REV
	 *
	 * MOT3-ON
	 * MOT3-OFF
	 * MOT3-REV
	 *
	 * MOT4-ON
	 * MOT4-OFF
	 * MOT4-REV
	 *
	 * MOT5-ON
	 * MOT5-OFF
	 * MOT5-REV
	 *
	 * MOT6-ON
	 * MOT6-OFF
	 * MOT6-REV
	 *
	 *****************/
#define CACT_MOT1NORM	0xff
#define CACT_MOT1REVE	0xfe
#define CACT_MOT1WAIT	0xfd
  
#define CACT_MOT2NORM	0xfb
#define CACT_MOT2REVE	0xfa
#define CACT_MOT2WAIT	0xf9
  
#define CACT_MOT3NORM	0xf7
#define CACT_MOT3REVE	0xf6
#define CACT_MOT3WAIT	0xf5
	
#define CACT_MOT4NORM	0xf3
#define CACT_MOT4REVE	0xf2
#define CACT_MOT4WAIT	0xf1

#define CACT_MOT5NORM	0xef
#define CACT_MOT5REVE	0xee
#define CACT_MOT5WAIT	0xed
	
#define CACT_MOT6NORM	0xeb
#define CACT_MOT6REVE	0xea
#define CACT_MOT6WAIT	0xe9

#define CACT_PWMLED		0xe4
#define CACT_MISC		0xe3

    paction_t_0		func;
   
    u16 actionTime;	/** ³ÖĞøÊ±¼ä **/
    u16 actionPara;	/** ¶¯×÷ĞèÒªµÄÆäËü²ÎÊı£¬ÈçVPidxË÷ÒıºÅ **/
    u8 actionType;	/** ¶¯×÷ÀàĞÍ. ËÆÓëÇ°ÃæµÄ²ÎÊıÓĞÖØµşÖ®ÏÓ£¬ÊÇÒ»¸öÇø±ğ¶¯×÷µÄÒÀ¾İ **/
    u8 __pad1;		/** ×Ö½Ú¶ÔÆë **/
}xdata action_t;


typedef struct actionQueue_s {
    //int	head;
	//int	tail;
    //int flag;
    
    u8	head;
	u8	tail;
    u8 flag;
	msgType_t stepMsgType;			/** ½×¶ÎÊÂ¼şÍê³ÉÏûÏ¢ **/
	msgType_t overMsgType;			/** ¶ÓÁĞÊÂ¼şÈ«²¿Íê³ÉÏûÏ¢ **/
	Timer_t *timer;
        #define ACTIONQUEUESIZE 16
    action_t buf[ACTIONQUEUESIZE];     /** 16 bytes **/
}xdata actionQueue_t;

#if	0
typedef struct pwm_s {
	u8 buf[8];
} pwm_t;
#endif

/************************************************/
typedef struct stepMotStat_s {
	/** è¡Œç¨‹æ§åˆ¶ **/
	u16	stepLimit;			//---ç”µæœºä¸€ä¸ªåŠ¨ä½œçš„æ­¥æ•°(è§’åº¦)é™åˆ¶
	//u8	stepCnt;			//---ç”µæœºè½¬è¿‡çš„æ­¥æ•°æ€»æ•°è®¡æ•°(çš„8å€)
	/*************************
	 * stapCnt_Flag = 
	 * 	0 - do nothing
	 * 	1 - stepCnt ascend
	 * 	2 - stepCnt discline until 0 
	 * 	3 - 
	 *  
	 *************************/	
	u8	stepCnt_Flag:3;		//---æ§åˆ¶è®¡æ•°å™¨ä½¿ç”¨
	
	/** é€Ÿåº¦å˜åŒ–(åŠ é€Ÿåº¦)æ§åˆ¶ **/
	/*************************
	 * stop = 
	 * 	0 - running
	 *	1 - stop and keep moment
	 *	2 - stop and release moment
	 *	3 - reversal
	 *************************/
	u8	stop:2;				/** è¿è¡Œã€åœæ­¢æ ‡å¿— **/
	/*************************
	 * stat = 
	 * 	0 - do nothing
	 * 	1 - step ascend
	 * 	2 - step discline
	 * 	3 - stop(with Holding moment)
	 * 	4 - stop(High Impedance)
	 *
	 *************************/
	 /** çŠ¶æ€æ§åˆ¶ **/
	u8	stat:3;				/** è¿è¡ŒçŠ¶æ€ï¼šæ­£åè½¬ **/
	
	/** é€Ÿåº¦æ§åˆ¶ - æ­¥è¿›é¢‘ç‡åˆ†é¢‘ **/
	u8	scale_dst:4;		/** å¯ä»¥ç†è§£ä¸ºæœ€ç»ˆç›®æ ‡(å»¶è¿Ÿæ—¶é—´å•ä½)é€Ÿåº¦çš„å€’æ•° **/
	u8	scale_bak:4;		/** å¯ä»¥ç†è§£ä¸ºä¸Šä¸€ä¸ªæ—¶é—´å•ä½çš„é€Ÿåº¦çš„å€’æ•° **/
	u8	scale:4;			/** å½“å‰éœ€è¦å»¶è¿Ÿçš„æ—¶é—´å•ä½ **/
	
	u8	step:4;
} stepMotStat_t;
typedef struct stepMot_s {
	
	#define	CMOT_NUM	(6)	//---ç”µæœºæ•°
	stepMotStat_t buf[CMOT_NUM];
} stepMot_t;
//} idata stepMot_t;
//} xdata stepMot_t;

#endif
