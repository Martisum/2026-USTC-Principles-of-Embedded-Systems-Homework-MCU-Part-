#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "leg.h"
#include "mode.h"
#include "OLED.h"
#include "OLED_Data.h"
#include "OLED_Content.h"        
#include "tianwen.h"
#include "bluetooth.h"


//串口1标志,接收到A赋值1，接收到B赋值2
u8 USART1_Sign = 0;

int main(void)
{	
	u32 i;
	//OLED显示数据
	u8 string[10]={0};
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	My_EXTI_Init();//按键中断初始化
	USART1_Init(115200);//串口1初始化
	USART2_Init(115200);
	USART3_Init(9600);
	OLED_Init();
	OLED_Clear();
	TIM4_CH1_Init(1999,719);//左前
	TIM4_CH2_Init(1999,719);//左后
	TIM4_CH3_Init(1999,719);//右后
	TIM4_CH4_Init(1999,719);//右后
	TIM3_CH1_Init(1999,719);//尾巴
	TIM_SetCompare1(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,150 );//占空比7.5%旋转90度
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();
	
	while(1)
	{	
		
		LED=!LED; //一轮运动闪一次
		
		if(Sign==1)
		{
			Advance();//前进
			bug++;//解决立正到前进的连贯问题
			if(Sign1!=0)
			{
				bug=0;
				Sign1=0;
			}
		}
		else if(Sign==2)
		{
			Queen();//后退
			bug++;
			if(Sign1!=0)
			{
				bug=0;
				Sign1=0;
			}
		}
		else if(Sign==3)
		{
			Left();//左转
		}
		else if(Sign==4)
		{
			Right();//右转
		}
		else if(Sign==5)
		{
			Stand();//站立
		}
		else if(Sign==6)
		{
			Rock();//摇摆
		}
		else if(Sign==7)
		{
			Handshake();//握手
		}
		else if(Sign==8)
		{
			Sleep();//睡觉
		}
		else if(Sign==9)
		{
			Sit();//坐
		}
		else if(Sign==10)
		{
			dance();//跳舞
		}
		else if(Sign==11)
		{
			pee();//撒尿
		}
		else if(Sign==12)
		{
			Stand();//立正
		}

		i++ ;
		delay_ms(10);
	}
}


