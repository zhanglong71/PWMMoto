
//#include	<reg52.h>
#include	"STC15W4K60S4.H"
#include "intrins.h"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
//#include "debug.h"
#include "driver.h"
#include "arch.h"
#include "main.h"

#include "IAP.h"
/*******************************************************************************/
#if	0
/*************************************
 * 关闭IAP
 *************************************/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
u8 IapReadByte(u16 addr)
{
    u8 dat;                       //数据缓冲区
#define ENABLE_IAP  0x82
#define CMD_READ    1               //IAP字节读命令
	
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                      //关闭IAP功能

    return dat;                     //返回
}

/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(u16 addr, u8 dat)
{
#define CMD_PROGRAM 2               //IAP字节编程命令
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}

/*----------------------------
扇区擦除
----------------------------*/
void IapEraseSector(u16 addr)
{
#define CMD_ERASE   3               //IAP扇区擦除命令
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}
#endif

/*******************************************************************************/
#if	0
/************************** �� ISP,IAP ���� *******************************/
void ISP_IAP_enable(void)
{
	EA	=	0;	/* ���ж� */
	ISP_CONTR	=	ISP_CONTR & 0x18;       /* 0001,1000 */
	ISP_CONTR	=	ISP_CONTR | WAIT_TIME;
	ISP_CONTR	=	ISP_CONTR | 0x80;       /* 1000,0000 */
}

/************************** �ر� ISP,IAP ���� ******************************/
void ISP_IAP_disable(void)
{
	ISP_CONTR	=	ISP_CONTR & 0x7f;	/* 0111,1111 */
	ISP_TRIG	=	0x00;
	EA			=   1;                /* ���ж� */
}

/************************** �ֽڶ� *****************************************/
INT8U IAP_read(INT16U byte_addr)
{
	ISP_ADDRH	=	(INT8U)(byte_addr >> 8);
	ISP_ADDRL	=	(INT8U)(byte_addr & 0x00ff);

	ISP_CMD		=	ISP_CMD	&	0xf8;        /* 1111,1000 */
	ISP_CMD		=	ISP_CMD	|	READ_AP_and_Data_Memory_Command;        /* 0000,0001 */

	ISP_IAP_enable();

	ISP_TRIG	=	0x46;
	ISP_TRIG	=	0xb9;
	_nop_();

	ISP_IAP_disable();
	return (ISP_DATA);
}

/**************************** �������� ***************************************/
INT8U IAP_erase(INT16U sector_addr)
{
	INT16U get_sector_addr	=	0;
	get_sector_addr			=	(sector_addr & 0xfe00); /* 1111,1110,0000,0000; ȡ������ַ */
	ISP_ADDRH        		=	(INT8U)(get_sector_addr >> 8);
	ISP_ADDRL		        =	0x00;

	ISP_CMD	=	ISP_CMD	&	0xf8;	/* 1111,1000 */
	ISP_CMD	=	ISP_CMD	|	SECTOR_ERASE_AP_and_Data_Memory_Command;	/* 0000,0011 */

	ISP_IAP_enable();
	ISP_TRIG	=	0x46;        /* ����ISP_IAP���� */
	ISP_TRIG	=	0xb9;        /* ����ISP_IAP���� */
	 _nop_();

	ISP_IAP_disable();
	return OK;
}

/****************************** �ֽڱ�̲�У�� *********************************/
INT8U IAP_pro_ver(INT16U byte_addr, INT8U original_data)
{
	ISP_ADDRH	=	(INT8U)(byte_addr >> 8);
	ISP_ADDRL	=	(INT8U)(byte_addr & 0x00ff);

	ISP_CMD		=	ISP_CMD	&	0xf8;        /* 1111,1000 */
	ISP_CMD		=	ISP_CMD	|	PROGRAM_AP_and_Data_Memory_Command;	/* 0000,0010 */
	ISP_DATA	=	original_data;

	ISP_IAP_enable();

	ISP_TRIG	=	0x46;
	ISP_TRIG	=	0xb9;
	_nop_();

	ISP_DATA	=	0x00;

	ISP_CMD		=	ISP_CMD	&	0xf8;        /* 1111,1000 */
	ISP_CMD		=	ISP_CMD	|	READ_AP_and_Data_Memory_Command;        /* 0000,0001 */

	ISP_TRIG	=	0x46;        /* ����ISP_IAP���� */
	ISP_TRIG	=	0xb9;        /* ����ISP_IAP���� */
	_nop_();

	ISP_IAP_disable();

	if(ISP_DATA	==	original_data)
		return	OK;
	else
		return	ERROR;
}

#endif
