#ifndef __DRIVER_H__
#define __DRIVER_H__


int sysProcess(msg_t *val);
u8 phrase_command(charQueue_t *src);
//void pwdTmr_set(u8 order, u8 value);
void setMoto_Speed(u8 __motNO, u8 __speed);

u8 pwrKey_Detect(void);
u8 TKInt_Detect(void);
u8 Ir_Detect(void);
u8 io_detect(void);
u8 motStat_detect(void);

//void IR_power_on(void);
//void IR_power_off(void);

void ADC_Init(void);
u8	ADC_get(void);

void timer0_Init(void);
/***************************************/
void motport_init(void);
/***************************************/

#endif