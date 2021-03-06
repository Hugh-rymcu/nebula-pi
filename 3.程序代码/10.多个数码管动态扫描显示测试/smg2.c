/*******************************************************************
*            数码管显示测试                                            
* ******************************************************************
* 【主芯片】：STC89SC52/STC12C5A60S2
* 【主频率】: 11.0592MHz 
*                                                                                                                               	
* 【版  本】： V1.0                                          	
* 【作  者】： stephenhugh                            	
* 【网  站】：https://rymcu.taobao.com/                              	
* 【邮  箱】：                                          	
*                                                                 	
* 【版  权】All Rights Reserved 
* 【声  明】此程序仅用于学习与参考，引用请注明版权和作者信息！
         
* 【功  能】数码管1~4循环显示数字1~4,动态扫描法，即变化速度很快，此处为2ms                                                           	
*******************************************************************/
#include<reg52.h>

#define uchar  unsigned char
#define uint unsigned int

#define FOSC 11059200 //单片机晶振频率
#define T_1ms (65536 - FOSC/12/1000)  //定时器初始值计算

uint count = 0;
uint flag  = 0;

sbit DU = P0^6;
sbit WE = P0^7;

//共阴型(0~9,A,b,C,d,E,F,全亮)
uchar code table_D[]={0x3F,0x06,0x5B,0x4F,
					0x66,0x6D,0x7D,0x07,
					0x7F,0x6F,0xEE,0x3e,
					0x9c,0x7a,0x9e,0x8e,
					0x00};

uchar code table_W[]={0x00,0x01,0x02,0x04,0x8};
//位选数组
//uchar code table_W[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xFF,0x00};
void main()
{
	TMOD = 0x01;	 //定时器工作模式配置
	TL0  = T_1ms;	//装载初始值
	TH0  = T_1ms>>8;

	TR0  = 1;		 //启动定时器
	ET0  = 1;		 //允许定时器中断
	EA   = 1;		 //开总中断

	while(1);	  //循环
}

void timer0() interrupt 1
{
	TL0 = T_1ms;//重装初始值
	TH0 = T_1ms>>8;

	count++;
	if(count>= 2)//每一毫秒进入一次中断，达到2次则为2ms,跟新一次数码管显示。
	{
		count = 0;

		P2 =~table_W[0];//关闭所有数码管，消隐处理
		WE = 1;
		WE = 0;
		
		flag++;

		P2 = table_D[flag];//数字1~4循环
		DU = 1;
		DU = 0;
	
		P2 = ~table_W[flag];//数码管1~4循环点亮
		WE = 1;
		WE = 0;

		
		if(flag>=4)
			flag =0;
	}
}
