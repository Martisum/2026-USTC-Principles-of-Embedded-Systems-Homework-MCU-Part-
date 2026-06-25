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
#include "OLED_Debug.h"
#include "stdio.h"	

extern char copy_hex_str[30];

//����1��־,���յ�A��ֵ1�����յ�B��ֵ2
u8 USART1_Sign = 0;

int main(void)
{	
	u32 i;
	//OLED��ʾ����
	// u8 string[10]={0};
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	My_EXTI_Init();//�����жϳ�ʼ��
	USART1_Init(115200);//����1��ʼ��
	USART2_Init(115200);
	USART3_Init(9600);
	OLED_Init();
	OLED_Clear();
	TIM4_CH1_Init(1999,719);//��ǰ
	TIM4_CH2_Init(1999,719);//���???
	TIM4_CH3_Init(1999,719);//�Һ�
	TIM4_CH4_Init(1999,719);//�Һ�
	TIM3_CH1_Init(1999,719);//β��
	TIM_SetCompare1(TIM4,150 );//ռ�ձ�7.5%��ת90��
	TIM_SetCompare2(TIM4,150 );//ռ�ձ�7.5%��ת90��
	TIM_SetCompare3(TIM4,150 );//ռ�ձ�7.5%��ת90��
	TIM_SetCompare4(TIM4,150 );//ռ�ձ�7.5%��ת90��
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();

	__enable_irq();
	OLED_Debug_Init();

	
	while(1)
	{	
		if (bt_data_ready)
		{
			OLED_ShowString(0, 8, copy_hex_str, OLED_6X8);
			OLED_Update();
			bt_data_ready = 0;
		}
		
		LED=!LED; //һ���˶���һ��
		
		if(Sign==1)
		{
			Advance();//ǰ��
			bug++;//���������ǰ������������???
			if(Sign1!=0)
			{
				bug=0;
				Sign1=0;
			}
		}
		else if(Sign==2)
		{
			Queen();//����
			bug++;
			if(Sign1!=0)
			{
				bug=0;
				Sign1=0;
			}
		}
		else if(Sign==3)
		{
			Left();//��ת
		}
		else if(Sign==4)
		{
			Right();//��ת
		}
		else if(Sign==5)
		{
			Stand();//վ��
		}
		else if(Sign==6)
		{
			Rock();//ҡ��
		}
		else if(Sign==7)
		{
			Handshake();//����
		}
		else if(Sign==8)
		{
			Sleep();//˯��
		}
		else if(Sign==9)
		{
			Sit();//��
		}
		else if(Sign==10)
		{
			dance();//����
		}
		else if(Sign==11)
		{
			pee();//����
		}
		else if(Sign==12)
		{
			Stand();//����
		}

		i++ ;
		delay_ms(10);
	}
}


