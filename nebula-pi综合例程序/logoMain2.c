														    #include<reg52.h>
#include"Drive_1602.h"


#define uchar unsigned char
#define  uint unsigned int

#define FOSC 11059200 //单片机晶振频率
#define T_1ms (65536 - FOSC/12/1000)  //定时器初始值计算

sbit FM = P2^4;//蜂鸣器
sbit DU = P2^7;//数码管段选、位选引脚定义
sbit WE = P2^6;
sbit DU_L = P2^3; 
	
uchar T_flag  = 0;
void delayms(unsigned int ms);//毫秒延时
void init_Gram(unsigned char T,unsigned char T1);//动态显示“荣易电子欢迎您！”
void write_CGRAM(uchar row);//写自定义字符
uchar code zifu[][8]={
		  { 4, 4,31, 4, 0,15, 8,17},
		  { 8, 8,31, 8, 0,31, 1, 2},
		  { 7, 4, 4, 7, 4, 4, 7, 2},
		  {28, 4, 4,28, 4, 4,28, 0},
		  { 1, 1, 1,15, 9, 9, 9,15},
		  { 0, 0, 0,28, 4, 4, 4,28},
		  { 0,15, 0, 0, 0, 1, 1,31},
		  { 0,28, 4, 8, 8,16, 0,31},//前八个字

		  { 0, 0,30, 2, 3,13,13, 6},
		  {16,16,16,30, 2, 4, 8, 8},
		  { 0, 8, 5, 5, 1, 1,29, 5},
		  { 0,16,14,10,10,10,10,10},
		  { 5, 5, 5,13,14,21, 5, 5},
		  { 0, 0,30, 2,12,12,12,10},
		  { 0, 4, 4, 4, 4, 4, 4, 4},
		  { 0, 0, 0, 0, 0, 0, 0, 0},//第二组八个字

		  { 1,15, 1, 3, 5,13,25, 1},
		  { 0,30,16, 8, 8, 4, 3, 0},
		  { 4, 7, 9, 9, 2, 4, 5, 1},
		  { 0,30,10,10,18,18,12, 4},
		  { 9, 9, 9,15, 9, 1, 1, 0},
		  { 4, 4, 4,28, 5, 1, 1,31},
		  { 1, 1, 1, 1, 1, 1, 3, 1},
		  { 0,0 , 0, 0, 0, 0, 0, 0},//第三组八个字

		  { 4,12,10,11,17, 1, 2, 4},
		  { 8,24,24, 4, 4, 4, 2, 1},
		  { 5, 5, 5, 5, 4,12,11, 0},
		  {10,30,12, 8, 8, 8,31, 0},
		  { 6, 5, 4, 1,13,13,20, 7},
		  {10, 8,16, 0, 2, 5, 5,28},
		  { 4, 4, 0, 0, 4, 4, 0, 0},
		  { 0, 0, 0, 0, 0, 0, 0, 0}//第四组八个
		};
void main()
{
	uchar i=0;
	uchar L=10;
	Init_1602();//1602初始化

	P0 = 0xff;//关闭所有数码管
	WE = 1;
	WE = 0; 
	DU_L = 1;

	init_Gram(255,1);//动态显示“荣易电子欢迎您！”
	//Disp_1602_str(1,1,"                ");//显示通道初始化
	 
	 while(1);
}


//毫秒延时函数
void delayms(unsigned int ms)
{
	unsigned int x,y;
	for(x=ms;x>0;x--)
		for(y=70;y>0;y--);
}
//动态显示“荣易电子欢迎您！” T:logo总共显示的次数，T1每闪烁间隔
void init_Gram(unsigned char T,unsigned char T1) 
{
	uchar L,i=0;
	uchar MS = 20;
	while(T--)
	{
		L=T1;
 		while(L--)
		{
			write_CGRAM(0);	//八个自定义字符写到GRAM中
			WR_Cmd(0x80);  //写开始地址
			for(i=0;i<8;i++)WR_Dat(i);//连续显示8个自定义字符
			delayms(MS); //延时
			WR_Cmd(0x01);//清除屏幕
			
			write_CGRAM(2);
			WR_Cmd(0xC0);
			for(i=0;i<8;i++)WR_Dat(i);
			delayms(MS);
			WR_Cmd(0x01);
	  	}
	  	L=T1;
  		while(L--)
		{
			write_CGRAM(1);
			WR_Cmd(0x88);
			for(i=8;i<16;i++)WR_Dat(i);
			delayms(MS);
			WR_Cmd(0x01);
			
			write_CGRAM(3);
			WR_Cmd(0xC8);
			for(i=8;i<16;i++)WR_Dat(i);
			delayms(MS);
			WR_Cmd(0x01);
	  	}
	}
}
/////////////////////////写自定义字符
void write_CGRAM(uchar row)//row=0~3
{
	uchar i,j;
	WR_Cmd(0x40);//写CGAM命令
	for(i=0;i<8;i++)
		for(j=0;j<8;j++)
		WR_Dat(zifu[i+row*8][j]);			
}



