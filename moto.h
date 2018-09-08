#ifndef __MOTO_H__
#define __MOTO_H__

//void setMoto_StepCnt(u8 __motNO, u8 __step);
//u16 getMoto_StepCnt(u8 __motNO);
void setMoto_stop(u8 __motNO);

void 	setFoot_forward(void);
void 	setFoot_backward(void);
void 	setFoot_turnLeft(void);
void 	setFoot_turnRight(void);
//void 	setFoot_stop(void);
void	setFoot_stop(u8 __brake);
void	setFoot_Speed(u8 __speed);


void	setHand_leftForward(void);
void	setHand_leftBackward(void);
void	setHand_leftStop(u8 __brake);
//void	setHand_leftStop(void);
void	setHand_leftSpeed(u8 __speed);

void	setHand_rightForward(void);
void	setHand_rightBackward(void);
//void	setHand_rightStop(void);
void	setHand_rightStop(u8 __brake);
void	setHand_rightSpeed(u8 __speed);

void	setNeck_left(void);
void	setNeck_right(void);
void	setNeck_LRstop(u8 __brake);

void	setNeck_LRSpeed(u8 __speed);
//void	setNeck_LRstepCnt(u8 __stepCnt);
//u8	getNeck_LRstepCnt(void);
void	setNeck_LRstepCntFlag(u8 __stepCnt);
void setNeck_LRstepLimit(u8 __step);
u8	getNeck_LRstepLimit(void);


void	setNeck_forward(void);
void	setNeck_backward(void);
//void	setNeck_FBstop(void);
void	setNeck_FBstop(u8 __brake);
void	setNeck_FBSpeed(u8 __speed);


#endif