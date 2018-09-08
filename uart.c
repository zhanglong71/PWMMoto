
//#include	<reg52.h>
#include	"STC15W4K60S4.H"
#include "CONST.h"
#include "ptype.h"
#include "macro.h"
#include "global.h"
//#include "debug.h"

//#include "driver.h"
#include "arch.h"
//#include "moto.h"
//#include "IAP.h"
//#include "main.h"
#include "uart.h"


void Uart1_Init(void) 
{
	#if	1
	EA = 0; 		//暂时关闭中断
	TMOD &= 0x0F;  //定时器1模式控制在高4位
	TMOD |= 0x20;    //定时器1工作在模式2，自动重装模式
	SCON = 0x50;     //串口工作在模式1
	TH1 = 256 - (MAIN_Fosc / (Baud_Rate * 12 * 16));  //计算定时器重装值
	TL1 = 256 - (MAIN_Fosc / (Baud_Rate * 12 * 16));
	PCON |= 0x80;    //串口波特率加倍
	ES = 1;         //串行中断允许
	TR1 = 1;        //启动定时器1
	REN = 1;        //允许接收 
	//EA = 1;         //允许中断
	#endif
	
}


void Uart2_Init(void)
{
//---	
	#if	1
	S2CON = 0x50;           //---8-bit variable UART
	T2L = ((65536 - (MAIN_Fosc/4/Baud_Rate)) & 0xff);
    T2H = (((65536 - (MAIN_Fosc/4/Baud_Rate)) >> 8) & 0xff);
	AUXR &= ~(1<<3);	//---定时器2用作内部时钟
	AUXR |=  (1<<2);	//---定时器2速度是8051定时器速度的12倍。即不分频
	AUXR |=  (1<<4);	//---允许定时器2运行
   // AUXR |= 0x14;            
    IE2 |= 0x01;		//---允许UART2中断               
    //EA = 1;			//---开启总中断
	#endif
}

//void Uart3_init(u8 baud){ //初始化串口3  P0.0->RXD3 P0.1->TXD3
void Uart3_init(void){ //初始化串口3  P0.0->RXD3 P0.1->TXD3
    /**
    u32 baudrate;
if (baud)
  baudrate=115200;
else
  baudrate=9600;
  **/
    S3CON = 0x50;           
    T3L = (65536 - (MAIN_Fosc/4/Baud_Rate));  
    T3H = (65536 - (MAIN_Fosc/4/Baud_Rate))>>8;
    T4T3M |= 0x02;           
    T4T3M |= 0x08;           
    IE2 |= 0x08;                 
    EA = 1;
}


/*************************************************************************/
void Uart4_Init(void) 
{
//---P0.2->RXD4 P0.3->TXD4	
	S4CON = 0x50;         
    T4L = (65536 - (MAIN_Fosc/4/Baud_Rate)) & 0xff; 
    T4H = ((65536 - (MAIN_Fosc/4/Baud_Rate)) >> 8) & 0xff;
    T4T3M |= 0x20;  //---定时器4速度是8051定时器速度的12倍。即不分频
    T4T3M |= 0x80;	//---允许定时器4运行
	
    //IE2 |= 0x10;  //---允许UART4中断
    IE2 &= ~(1 << 4);  //---禁止UART4中断
    //EA = 1;	//---开启总中断
}


/*** uart1/2 send***/
void uart1_Send(void)
{
	u8 ch;
	
	if(g_uart_Tx_busy) return;
	if(charQueueOut_irq(&g_charTxQueue, &ch) == TRUE) {
		SBUF = ch;
		S2BUF = ch;
		g_uart_Tx_busy = 1;	
    }
}

void uart3_send(void)
{ 
#if 0
	//串口3发送
	#if	1
	u8 ch;
	
	if(g_uart3_Tx_busy) return;
	if(charQueueOut_irq(&g_charTx3Queue, &ch) == TRUE) {
		S3BUF = ch;
		g_uart3_Tx_busy = 1;	
    }
	
	#else
	S3BUF = c;            
	while (!(S3CON & S3TI));
	S3CON &= ~S3TI;     	
	#endif
   return ;
#endif
}
