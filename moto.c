#include	"STC15W4K60S4.H"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
//#include "debug.h"
#include "driver.h"
#include "arch.h"
#include "moto.h"
#include "main.h"


//---左轮
void mot1_ALL_L(void){MMOT_STEP_ALL_L(1);}
void mot1_step1(void){MMOT_STEP(1, 1);}
void mot1_step2(void){MMOT_STEP(1, 2);}
void mot1_step3(void){MMOT_STEP(1, 3);}
void mot1_step4(void){MMOT_STEP(1, 4);}
void mot1_step5(void){MMOT_STEP(1, 5);}
void mot1_step6(void){MMOT_STEP(1, 6);}
void mot1_step7(void){MMOT_STEP(1, 7);}
void mot1_step8(void){MMOT_STEP(1, 8);}

//---右轮
void mot2_ALL_L(void){MMOT_STEP_ALL_L(2);}
void mot2_step1(void){MMOT_STEP(2, 1);}
void mot2_step2(void){MMOT_STEP(2, 2);}
void mot2_step3(void){MMOT_STEP(2, 3);}
void mot2_step4(void){MMOT_STEP(2, 4);}
void mot2_step5(void){MMOT_STEP(2, 5);}
void mot2_step6(void){MMOT_STEP(2, 6);}
void mot2_step7(void){MMOT_STEP(2, 7);}
void mot2_step8(void){MMOT_STEP(2, 8);}

//---左手
void mot3_ALL_L(void){MMOT_STEP_ALL_L(3);}
void mot3_step1(void){MMOT_STEP(3, 1);}
void mot3_step2(void){MMOT_STEP(3, 2);}
void mot3_step3(void){MMOT_STEP(3, 3);}
void mot3_step4(void){MMOT_STEP(3, 4);}
void mot3_step5(void){MMOT_STEP(3, 5);}
void mot3_step6(void){MMOT_STEP(3, 6);}
void mot3_step7(void){MMOT_STEP(3, 7);}
void mot3_step8(void){MMOT_STEP(3, 8);}

//---右手
void mot4_ALL_L(void){MMOT_STEP_ALL_L(4);}
void mot4_step1(void){MMOT_STEP(4, 1);}
void mot4_step2(void){MMOT_STEP(4, 2);}
void mot4_step3(void){MMOT_STEP(4, 3);}
void mot4_step4(void){MMOT_STEP(4, 4);}
void mot4_step5(void){MMOT_STEP(4, 5);}
void mot4_step6(void){MMOT_STEP(4, 6);}
void mot4_step7(void){MMOT_STEP(4, 7);}
void mot4_step8(void){MMOT_STEP(4, 8);}

//---摇头
void mot5_ALL_L(void){MMOT_STEP_ALL_L(5);}
void mot5_step1(void){MMOT_STEP(5, 1);}
void mot5_step2(void){MMOT_STEP(5, 2);}
void mot5_step3(void){MMOT_STEP(5, 3);}
void mot5_step4(void){MMOT_STEP(5, 4);}
void mot5_step5(void){MMOT_STEP(5, 5);}
void mot5_step6(void){MMOT_STEP(5, 6);}
void mot5_step7(void){MMOT_STEP(5, 7);}
void mot5_step8(void){MMOT_STEP(5, 8);}

//---点头
void mot6_ALL_L(void){MMOT_STEP_ALL_L(6);}
void mot6_step1(void){MMOT_STEP(6, 1);}
void mot6_step2(void){MMOT_STEP(6, 2);}
void mot6_step3(void){MMOT_STEP(6, 3);}
void mot6_step4(void){MMOT_STEP(6, 4);}
void mot6_step5(void){MMOT_STEP(6, 5);}
void mot6_step6(void){MMOT_STEP(6, 6);}
void mot6_step7(void){MMOT_STEP(6, 7);}
void mot6_step8(void){MMOT_STEP(6, 8);}

code paction_t_0 g_motStepFunc_tab[][8] = {
	{mot1_step1, mot1_step2, mot1_step3, mot1_step4, mot1_step5, mot1_step6, mot1_step7, mot1_step8},
	{mot2_step1, mot2_step2, mot2_step3, mot2_step4, mot2_step5, mot2_step6, mot2_step7, mot2_step8},
	{mot3_step1, mot3_step2, mot3_step3, mot3_step4, mot3_step5, mot3_step6, mot3_step7, mot3_step8},
	{mot4_step1, mot4_step2, mot4_step3, mot4_step4, mot4_step5, mot4_step6, mot4_step7, mot4_step8},
	{mot5_step1, mot5_step2, mot5_step3, mot5_step4, mot5_step5, mot5_step6, mot5_step7, mot5_step8},
	{mot6_step1, mot6_step2, mot6_step3, mot6_step4, mot6_step5, mot6_step6, mot6_step7, mot6_step8},
};

code paction_t_0 g_motStep_ALL_L[] = {
	mot1_ALL_L,
	mot2_ALL_L,
	mot3_ALL_L,
	mot4_ALL_L,
	mot5_ALL_L,
	mot6_ALL_L,
};

/*****************************************************
 * id- x    - step
 * 0 - 0 	- 0
 * 1 - 15度 - 17
 * 2 - 30度 - 33
 * 3 - 45度 - 50
 * 4 - 60度 - 67
 * 5 - 75度 - 83
 * 6 - 90度 - 100
 * 	...
 * 12 - 180度 - 200
 *
 *****************************************************/
code u16 g_stepLimitScale_table[] = {
	0,			//---0 - 0度
	17,			//---1 - 15
	33,			//---2 - 30
	
#if	0
	50,			//---3 - 45
	67,			//---4 - 60
	83,			//---5 - 75
	100,		//---6 - 90
	117,		//---7 - 105
	133,		//---8 - 120
	150,		//---9 - 135
	167,		//---10 - 150
	183,		//---11 - 165
	200,		//---12 - 180
	217,		//---13 - 195
	233,		//---14 - 210
	250,		//---15 - 225
	267,		//---16 - 240
	283,		//---17 - 255
	300,		//---18 - 270
	317,		//---19 - 285
	333,		//---20 - 300
	350,		//---21 - 315
	367,		//---22 - 330
	383,		//---23 - 345
	400,		//---24 - 360
#endif
};

#if	0
/***************************************************************/
void setMoto_Speed(u8 __motNO, u8 __speed)
{
	MMOT_SPEED(__motNO, __speed);
}
/***************************************************************/

void setMoto_StepCnt(u8 __motNO, u8 __step)
{
	MSETMOT_STEPCNT(__motNO, __step);
}

u16 getMoto_StepCnt(u8 __motNO)
{
	return	MGETMOT_STEPCNT(__motNO);
}
#endif

/***************************************************************/
void setMoto_stop(u8 __motNO)
{
	g_stepMot_stat.buf[__motNO].stop = 1;	
}

/***************************************************************/

/****** foot ***************************************************/
void setFoot_StepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[0].stepCnt_Flag = 0;
		g_stepMot_stat.buf[1].stepCnt_Flag = 0;
	//} else if(__step  == 1) {
	} else {
		g_stepMot_stat.buf[0].stepCnt_Flag = 2;
		g_stepMot_stat.buf[1].stepCnt_Flag = 2;
		
		g_stepMot_stat.buf[0].stepLimit = MID2STEP(__step);
		g_stepMot_stat.buf[1].stepLimit = MID2STEP(__step);
		//g_stepMot_stat.buf[0].stepLimit = __step;
		//g_stepMot_stat.buf[1].stepLimit = __step;
//		g_stepMot_stat.buf[0].stepCnt = __step;
//		g_stepMot_stat.buf[1].stepCnt = __step;
	}
}
u8 getFoot_StepLimit(void)
{
	return	g_stepMot_stat.buf[0].stepLimit;
	//return	g_stepMot_stat.buf[1].stepLimit ;
	//return	(g_stepMot_stat.buf[1].stepLimit + g_stepMot_stat.buf[0].stepLimit)/2;
}
void	setFoot_Speed(u8 __speed)
{
	g_stepMot_stat.buf[0].scale_dst = __speed;
	g_stepMot_stat.buf[1].scale_dst = __speed;
	
	//g_stepMot_stat.buf[0].scale_bak = 15;
	//g_stepMot_stat.buf[1].scale_bak = 15;
	g_stepMot_stat.buf[0].scale_bak = __speed;
	g_stepMot_stat.buf[1].scale_bak = __speed;
}
//---moto1
void setFoot_forward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[0].stop = 0;
	g_stepMot_stat.buf[0].stat = 1;	//---左轮向前
	g_stepMot_stat.buf[0].step = 0;
	
	g_stepMot_stat.buf[1].stop = 0;
	g_stepMot_stat.buf[1].stat = 1;	//---右轮向前
	g_stepMot_stat.buf[1].step = 0;
	
	
}

void setFoot_backward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[0].stop = 0;
	g_stepMot_stat.buf[0].stat = 2;	//---左轮向后
	g_stepMot_stat.buf[0].step = 0;
	
	g_stepMot_stat.buf[1].stop = 0;
	g_stepMot_stat.buf[1].stat = 2;	//---右轮向后
	g_stepMot_stat.buf[1].step = 0;
}

void setFoot_turnLeft(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[0].stop = 0;
	g_stepMot_stat.buf[0].stat = 2;	//---左轮向后
	g_stepMot_stat.buf[0].step = 0;
	
	g_stepMot_stat.buf[1].stop = 0;
	g_stepMot_stat.buf[1].stat = 1;	//---右轮向前
	g_stepMot_stat.buf[1].step = 0;
}

void setFoot_turnRight(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[0].stop = 0;
	g_stepMot_stat.buf[0].stat = 1;	//---左轮向前
	g_stepMot_stat.buf[0].step = 0;
	
	g_stepMot_stat.buf[1].stop = 0;
	g_stepMot_stat.buf[1].stat = 2;	//---右轮向后
	g_stepMot_stat.buf[1].step = 0;
}

void	setFoot_stop(u8 __brake)
{
	MMOT_SLEEP(0);
	if(__brake == 0) {
		g_stepMot_stat.buf[0].stop = 2;	
		g_stepMot_stat.buf[1].stop = 2;	
	} else if(__brake == 1){
		g_stepMot_stat.buf[0].stop = 1;	
		g_stepMot_stat.buf[1].stop = 1;	
	}
}

/********************************************
 * set left foot step Limit 
 * 
 ********************************************/
void setFoot_leftStepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[0].stepCnt_Flag = 0;
	} else {
		g_stepMot_stat.buf[0].stepCnt_Flag = 2;
		
		//g_stepMot_stat.buf[0].stepLimit = __step;
		g_stepMot_stat.buf[0].stepLimit = MID2STEP(__step);
	}
}
u8 getFoot_leftStepLimit(void)
{
	return	g_stepMot_stat.buf[0].stepLimit;
}

void	setFoot_leftStepCntFlag(u8 __stepCnt)
{
	MSETMOT_STEPFLAG(0, (__stepCnt & 0xF));
}
#if	0
void	setFoot_leftStepCnt(u8 __stepCnt)
{
	MSETMOT_STEPCNT(0, __stepCnt);
}
#endif

#if	0
u8	getFoot_leftStepCnt(void)
{
	return	MGETMOT_STEPCNT(0);
}
#endif

#if	1
void	setFoot_leftSpeed(u8 __speed)
{
	g_stepMot_stat.buf[0].scale_dst = __speed;
	//g_stepMot_stat.buf[0].scale_bak = 15;
	g_stepMot_stat.buf[0].scale_bak = __speed;
}
//---moto1
void setFoot_leftForward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[0].stop = 0;
	g_stepMot_stat.buf[0].stat = 1;	//---右轮向前
	g_stepMot_stat.buf[0].step = 0;
	
}

void setFoot_leftBackward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[0].stop = 0;
	g_stepMot_stat.buf[0].stat = 2;	//---右轮向后
	g_stepMot_stat.buf[0].step = 0;
	
}

//void setFoot_leftStop(void)
void setFoot_leftStop(u8 __brake)
{
	MMOT_SLEEP(0);
	#if	0
	g_stepMot_stat.buf[0].stop = 1;	
	#else
	if(__brake == 0) {
		g_stepMot_stat.buf[0].stop = 2;	
	} else if(__brake == 1){
		g_stepMot_stat.buf[0].stop = 1;	
	}
	#endif
}
#endif

/**** right foot *******************************************/
#if	1
void setFoot_rightStepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[1].stepCnt_Flag = 0;
	} else {
		g_stepMot_stat.buf[1].stepCnt_Flag = 2;
		
		g_stepMot_stat.buf[1].stepLimit = MID2STEP(__step);
		//g_stepMot_stat.buf[1].stepLimit = __step;
//		g_stepMot_stat.buf[1].stepCnt = __step;
	}
}
u8 getFoot_rightStepLimit(void)
{
	return	g_stepMot_stat.buf[1].stepLimit;
}

void	setFoot_rightStepCntFlag(u8 __stepCnt)
{
	MSETMOT_STEPFLAG(1, (__stepCnt & 0xF));
}
#if	0
void	setFoot_rightStepCnt(u8 __stepCnt)
{
	MSETMOT_STEPCNT(1, __stepCnt);
}

u8	getFoot_rightStepCnt(void)
{
	return	MGETMOT_STEPCNT(1);
}
#endif

void	setFoot_rightSpeed(u8 __speed)
{
	g_stepMot_stat.buf[1].scale_dst = __speed;
	//g_stepMot_stat.buf[1].scale_bak = 15;
	g_stepMot_stat.buf[1].scale_bak = __speed;
}

void setFoot_rightForward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[1].stop = 0;
	g_stepMot_stat.buf[1].stat = 1;	//---右轮向前
	g_stepMot_stat.buf[1].step = 0;
	
}

void setFoot_rightBackward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[1].stop = 0;
	g_stepMot_stat.buf[1].stat = 2;	//---右轮向后
	g_stepMot_stat.buf[1].step = 0;
	
}

//void setFoot_rightStop(void)
void setFoot_rightStop(u8 __brake)
{
	MMOT_SLEEP(0);
	#if	0
	g_stepMot_stat.buf[1].stop = 1;	
	#else
	if(__brake == 0) {
		g_stepMot_stat.buf[1].stop = 2;	
	} else if(__brake == 1){
		g_stepMot_stat.buf[1].stop = 1;	
	}
	#endif
}
#endif


/**** left hander ******************************************/
void setHand_leftStepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[2].stepCnt_Flag = 0;
	} else {
		g_stepMot_stat.buf[2].stepCnt_Flag = 2;
		
		g_stepMot_stat.buf[2].stepLimit = MID2STEP(__step);
		//g_stepMot_stat.buf[2].stepLimit = __step;
//		g_stepMot_stat.buf[2].stepCnt = __step;
	}
}
u8 getHand_leftStepLimit(void)
{
	return	g_stepMot_stat.buf[2].stepLimit;
}

void	setHand_leftStepCntFlag(u8 __stepCnt)
{
	MSETMOT_STEPFLAG(2, (__stepCnt & 0xF));
}

#if	0
void	setHand_leftStepCnt(u8 __stepCnt)
{
	MSETMOT_STEPCNT(2, __stepCnt);
}

u8	getHand_leftStepCnt(void)
{
	return	MGETMOT_STEPCNT(2);
}
#endif

void	setHand_leftSpeed(u8 __speed)
{
	g_stepMot_stat.buf[2].scale_dst = __speed;
	//g_stepMot_stat.buf[2].scale_bak = 15;
	g_stepMot_stat.buf[2].scale_bak = __speed;
}
void	setHand_leftForward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[2].stop = 0;
	g_stepMot_stat.buf[2].stat = 1;
	g_stepMot_stat.buf[2].step = 0;
	
}

void	setHand_leftBackward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[2].stop = 0;
	g_stepMot_stat.buf[2].stat = 2;
	g_stepMot_stat.buf[2].step = 0;
	
}

void	setHand_leftStop(u8 __brake)
{
	MMOT_SLEEP(0);
	if(__brake == 0) {
		g_stepMot_stat.buf[2].stop = 2;	
	} else if(__brake == 1){
		g_stepMot_stat.buf[2].stop = 1;	
	}
}

/**** right hander ******************************************/
void setHand_rightStepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[3].stepCnt_Flag = 0;
	} else {
		g_stepMot_stat.buf[3].stepCnt_Flag = 2;
		
		g_stepMot_stat.buf[3].stepLimit = MID2STEP(__step);
		//g_stepMot_stat.buf[3].stepLimit = __step;
//		g_stepMot_stat.buf[3].stepCnt = __step;
	}
}
u8 getHand_rightStepLimit(void)
{
	return	g_stepMot_stat.buf[3].stepLimit;
}

void	setHand_rightStepCntFlag(u8 __stepCnt)
{
	MSETMOT_STEPFLAG(3, (__stepCnt & 0xF));
}

#if	0
void	setHand_rightStepCnt(u8 __stepCnt)
{
	MSETMOT_STEPCNT(3, __stepCnt);
}

u8	getHand_rightStepCnt(void)
{
	return	MGETMOT_STEPCNT(3);
}
#endif

void	setHand_rightSpeed(u8 __speed)
{
	g_stepMot_stat.buf[3].scale_dst = __speed;
	//g_stepMot_stat.buf[3].scale_bak = 15;
	g_stepMot_stat.buf[3].scale_bak = __speed;
}
void	setHand_rightForward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[3].stop = 0;
	g_stepMot_stat.buf[3].stat = 1;
	g_stepMot_stat.buf[3].step = 0;
	
}
void	setHand_rightBackward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[3].stop = 0;
	g_stepMot_stat.buf[3].stat = 2;
	g_stepMot_stat.buf[3].step = 0;
		
}

void	setHand_rightStop(u8 __brake)
{
	MMOT_SLEEP(0);
	if(__brake == 0) {
		g_stepMot_stat.buf[3].stop = 2;	
	} else if(__brake == 1){
		g_stepMot_stat.buf[3].stop = 1;	
	}
}

/**** neck left right ******************************************/
void setNeck_LRstepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[4].stepCnt_Flag = 0;
	} else {
		g_stepMot_stat.buf[4].stepCnt_Flag = 2;
		
		g_stepMot_stat.buf[4].stepLimit = MID2STEP(__step);
		//g_stepMot_stat.buf[4].stepLimit = __step;
//		g_stepMot_stat.buf[4].stepCnt = __step;
	}
}
u8 getNeck_LRstepLimit(void)
{
	return	g_stepMot_stat.buf[4].stepLimit;
}

void	setNeck_LRstepCntFlag(u8 __stepCnt)
{
	MSETMOT_STEPFLAG(4, (__stepCnt & 0xF));
}

#if	0
void	setNeck_LRstepCnt(u8 __stepCnt)
{
	MSETMOT_STEPCNT(4, __stepCnt);
}

u8	getNeck_LRstepCnt(void)
{
	return	MGETMOT_STEPCNT(4);
}
#endif

void	setNeck_LRSpeed(u8 __speed)
{
	g_stepMot_stat.buf[4].scale_dst = __speed;
	//g_stepMot_stat.buf[4].scale_bak = 15;
	g_stepMot_stat.buf[4].scale_bak = __speed;
}
//---moto5
void	setNeck_left(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[4].stop = 0;	
	g_stepMot_stat.buf[4].stat = 1;
	g_stepMot_stat.buf[4].step = 0;
	
	
//	g_stepMot_stat.buf[4].stepCnt = g_stepMot_stat.buf[4].stepLimit;
}

void	setNeck_right(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[4].stop = 0;	
	g_stepMot_stat.buf[4].stat = 2;
	g_stepMot_stat.buf[4].step = 0;
	
	
//	g_stepMot_stat.buf[4].stepCnt = g_stepMot_stat.buf[4].stepLimit;
}


void	setNeck_LRstop(u8 __brake)
{
	MMOT_SLEEP(0);
	if(__brake == 0) {
		g_stepMot_stat.buf[4].stop = 2;	
	} else if(__brake == 1){
		g_stepMot_stat.buf[4].stop = 1;	
	}
}

/**** neck forward or backward ******************************************/
/** 设定步数上限 **/
void setNeck_FBstepLimit(u8 __step)
{
	if(__step  == 0) {
		g_stepMot_stat.buf[5].stepCnt_Flag = 0;
	} else {
		g_stepMot_stat.buf[5].stepCnt_Flag = 2;
		
		g_stepMot_stat.buf[5].stepLimit = MID2STEP(__step);
		//g_stepMot_stat.buf[5].stepLimit = __step;
//		g_stepMot_stat.buf[5].stepCnt = __step;
	}
}
/** 获取步数上限 **/
u8 getNeck_FBstepLimit(void)
{
	return	g_stepMot_stat.buf[5].stepLimit;
}
/** 获取步数限制 **/
void	setNeck_FBstepCntFlag(u8 __stepCnt)
{
	MSETMOT_STEPFLAG(5, (__stepCnt & 0xF));
}

#if	0
void	setNeck_FBstepCnt(u8 __stepCnt)
{
	MSETMOT_STEPCNT(5, __stepCnt);
}

u8	getNeck_FBstepCnt(void)
{
	return	MGETMOT_STEPCNT(5);
}
#endif

void	setNeck_FBSpeed(u8 __speed)
{
	g_stepMot_stat.buf[5].scale_dst = __speed;
	//g_stepMot_stat.buf[5].scale_bak = 15;
	g_stepMot_stat.buf[5].scale_bak = __speed;
}
//---moto6
void	setNeck_forward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[5].stop = 0;
	g_stepMot_stat.buf[5].stat = 1;
	g_stepMot_stat.buf[5].step = 0;
		
}

void	setNeck_backward(void)
{
	MMOT_SLEEP(0);
	g_stepMot_stat.buf[5].stop = 0;
	g_stepMot_stat.buf[5].stat = 2;
	g_stepMot_stat.buf[5].step = 0;
	
}

void	setNeck_FBstop(u8 __brake)
{
	MMOT_SLEEP(0);
	if(__brake == 0) {
		g_stepMot_stat.buf[5].stop = 2;	
	} else if(__brake == 1) {
		g_stepMot_stat.buf[5].stop = 1;	
	}
}
/************************************************************************/

/** note: the order consistent with COMMAND protocal **/
void	doNothing(void) {}
code paction_t_0 g_partActionTable[] = {
	doNothing,	//---0x00(nothing)
	setFoot_forward,	//---0x01
	setFoot_backward,	//---0x02
	setFoot_turnLeft,	//---0x03
	setFoot_turnRight,	//---0x04
	doNothing,	//---0x05(stop)
	doNothing,	//---0x06(nothing)
	doNothing,	//---0x07(nothing)
	setHand_leftForward,	//---0x08
	setHand_leftBackward,	//---0x09
	doNothing,	//---0x0a(stop)
	doNothing,	//---0x0b(nothing)
	doNothing,	//---0x0c(nothing)
	doNothing,	//---0x0d(nothing)
	doNothing,	//---0x0e(nothing)
	doNothing,	//---0x0f(nothing)
	setHand_rightForward,	//---0x10
	setHand_rightBackward,	//---0x11
	doNothing,	//---0x12(stop)
	doNothing,	//---0x13(nothing)
	doNothing,	//---0x14(nothing)
	doNothing,	//---0x15(nothing)
	doNothing,	//---0x16(nothing)
	doNothing,	//---0x17(nothing)
	setNeck_left,		//---0x18
	setNeck_right,		//---0x19
	doNothing,	//---0x1a(stop)
	doNothing,	//---0x1b(nothing)
	doNothing,	//---0x1c(nothing)
	doNothing,	//---0x1d(nothing)
	doNothing,	//---0x1e(nothing)
	doNothing,	//---0x1f(nothing)
	setNeck_forward,	//---0x20
	setNeck_backward,	//---0x21
	doNothing,	//---0x22(stop)
	doNothing,	//---0x23(nothing)
	doNothing,	//---0x24(nothing)
	doNothing,	//---0x25(nothing)
	doNothing,	//---0x26(nothing)
	doNothing,	//---0x27(nothing)
	doNothing,	//---0x28(nothing)
	doNothing,	//---0x29(nothing)
	doNothing,	//---0x2a(nothing)
	doNothing,	//---0x2b(nothing)
	doNothing,	//---0x2c(nothing)
	doNothing,	//---0x2d(nothing)
	doNothing,	//---0x2e(nothing)
	doNothing,	//---0x2f(nothing)
	doNothing,	//---0x30(nothing)
	setFoot_leftForward,	//---0x31
	setFoot_leftBackward,	//---0x32
	doNothing,		//---0x33(stop)
	setFoot_rightForward,	//---0x34
	setFoot_rightBackward,	//---0x35
	doNothing,		//---0x36(stop)

};

code paction_t_1 g_setSpeedTable[] = {
	doNothing,	//---0x00(nothing)
	setFoot_Speed,	//---0x01
	setFoot_Speed,	//---0x02
	setFoot_Speed,	//---0x03
	setFoot_Speed,	//---0x04
	setFoot_stop,	//---0x05(stop)
	doNothing,	//---0x06(nothing)
	doNothing,	//---0x07(nothing)
	setHand_leftSpeed,	//---0x08
	setHand_leftSpeed,	//---0x09
	setHand_leftStop,	//---0x0a(stop)
	doNothing,	//---0x0b(nothing)
	doNothing,	//---0x0c(nothing)
	doNothing,	//---0x0d(nothing)
	doNothing,	//---0x0e(nothing)
	doNothing,	//---0x0f(nothing)
	setHand_rightSpeed,	//---0x10
	setHand_rightSpeed,	//---0x11
	setHand_rightStop,	//---0x12(stop)
	doNothing,	//---0x13(nothing)
	doNothing,	//---0x14(nothing)
	doNothing,	//---0x15(nothing)
	doNothing,	//---0x16(nothing)
	doNothing,	//---0x17(nothing)
	setNeck_LRSpeed,	//---0x18
	setNeck_LRSpeed,	//---0x19
	setNeck_LRstop,		//---0x1a(stop)
	doNothing,	//---0x1b(nothing)
	doNothing,	//---0x1c(nothing)
	doNothing,	//---0x1d(nothing)
	doNothing,	//---0x1e(nothing)
	doNothing,	//---0x1f(nothing)
	setNeck_FBSpeed,	//---0x20
	setNeck_FBSpeed,	//---0x21
	setNeck_FBstop,		//---0x22(stop)
	doNothing,	//---0x23(nothing)
	doNothing,	//---0x24(nothing)
	doNothing,	//---0x25(nothing)
	doNothing,	//---0x26(nothing)
	doNothing,	//---0x27(nothing)
	doNothing,	//---0x28(nothing)
	doNothing,	//---0x29(nothing)
	doNothing,	//---0x2a(nothing)
	doNothing,	//---0x2b(nothing)
	doNothing,	//---0x2c(nothing)
	doNothing,	//---0x2d(nothing)
	doNothing,	//---0x2e(nothing)
	doNothing,	//---0x2f(nothing)
	doNothing,	//---0x30(nothing)
	setFoot_leftSpeed,	//---0x31
	setFoot_leftSpeed,	//---0x32
	setFoot_leftStop,		//---0x33(stop)
	setFoot_rightSpeed,	//---0x34
	setFoot_rightSpeed,	//---0x35
	setFoot_rightStop,		//---0x36(stop)
};

code paction_t_1 g_setStepLimitTable[] = {
	doNothing,	//---0x00(nothing)
	setFoot_StepLimit,	//---0x01
	setFoot_StepLimit,	//---0x02
	setFoot_StepLimit,	//---0x03
	setFoot_StepLimit,	//---0x04
	doNothing,	//---0x05(nothing)
	doNothing,	//---0x06(nothing)
	doNothing,	//---0x07(nothing)
	setHand_leftStepLimit,	//---0x08
	setHand_leftStepLimit,	//---0x09
	doNothing,	//---0x0a(nothing)
	doNothing,	//---0x0b(nothing)
	doNothing,	//---0x0c(nothing)
	doNothing,	//---0x0d(nothing)
	doNothing,	//---0x0e(nothing)
	doNothing,	//---0x0f(nothing)
	setHand_rightStepLimit,	//---0x10
	setHand_rightStepLimit,	//---0x11
	doNothing,	//---0x12(nothing)
	doNothing,	//---0x13(nothing)
	doNothing,	//---0x14(nothing)
	doNothing,	//---0x15(nothing)
	doNothing,	//---0x16(nothing)
	doNothing,	//---0x17(nothing)
	setNeck_LRstepLimit,	//---0x18
	setNeck_LRstepLimit,	//---0x19
	doNothing,	//---0x1a(nothing)
	doNothing,	//---0x1b(nothing)
	doNothing,	//---0x1c(nothing)
	doNothing,	//---0x1d(nothing)
	doNothing,	//---0x1e(nothing)
	doNothing,	//---0x1f(nothing)
	setNeck_FBstepLimit,	//---0x20
	setNeck_FBstepLimit,	//---0x21
	doNothing,	//---0x22(nothing)
	doNothing,	//---0x23(nothing)
	doNothing,	//---0x24(nothing)
	doNothing,	//---0x25(nothing)
	doNothing,	//---0x26(nothing)
	doNothing,	//---0x27(nothing)
	doNothing,	//---0x28(nothing)
	doNothing,	//---0x29(nothing)
	doNothing,	//---0x2a(nothing)
	doNothing,	//---0x2b(nothing)
	doNothing,	//---0x2c(nothing)
	doNothing,	//---0x2d(nothing)
	doNothing,	//---0x2e(nothing)
	doNothing,	//---0x2f(nothing)
	doNothing,	//---0x30(nothing)
	setFoot_leftStepLimit,	//---0x31
	setFoot_leftStepLimit,	//---0x32
	setFoot_leftStepLimit,	//doNothing,		//---0x33	
	setFoot_rightStepLimit,	//---0x34
	setFoot_rightStepLimit,	//---0x35
	setFoot_rightStepLimit,	//doNothing,		//---0x36
};

/************************************************************************/