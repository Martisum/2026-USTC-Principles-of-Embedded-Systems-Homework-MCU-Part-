#include "bluetooth.h"
#include "infrared.h"
#include "OLED_Debug.h"
#include <stdio.h>
#include <string.h>
#include "delay.h"

char copy_hex_str[30]={0};
volatile uint8_t bt_data_ready = 0;   /* 新数据标志，主循环查询 */

u8 Sign1=0;
int USART3_Sign = 20;
u8 Blue_data[6];

/* JDY-23 AT指令响应相关全局变量 */
char JDY_MAC_Str[18] = {0};
volatile uint8_t jdy_at_mode = 0;
char jdy_at_response[64];
volatile uint8_t jdy_at_idx = 0;
volatile uint8_t jdy_at_done = 0;

void USART3_Init(u32 baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate=baud;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART3,&USART_InitStructure);


	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
}


void USART3_IRQHandler(void)
{
	static char bt_buf[30] = {0};
	static uint8_t bt_idx = 0;
	uint8_t byte;

	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		byte = USART_ReceiveData(USART3);
		LED = !LED;

		/* 只累积字节到缓冲区，不操作OLED（避免慢速I2C导致USART溢出） */
		if (bt_idx < sizeof(bt_buf) - 1)
		{
			bt_buf[bt_idx++] = byte;
		}
		else
		{
			/* 缓冲区满，整体左移1字节腾出空间（滑动窗口） */
			memmove(bt_buf, bt_buf + 1, sizeof(bt_buf) - 2);
			bt_buf[sizeof(bt_buf) - 2] = byte;
		}
		bt_buf[bt_idx] = '\0';          /* 保持字符串合法 */

		/* 复制到全局变量，通知主循环有新数据 */
		strcpy(copy_hex_str, bt_buf);
		bt_data_ready = 1;

		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}

	/**************************************************************************
	 * 旧版蓝牙指令解析代码（已注释，保留备查）
	 **************************************************************************/
//	//OLED显示数据
//	u8 string[10]={0};
//	 static int i=0;
//
//	if(USART_GetITStatus(USART3, USART_IT_RXNE)!=RESET)
//	{
////		OLED_Clear();
//		LED=!LED;
//		Blue_data[i++]=USART_ReceiveData(USART3);
//		if(i==2)i=0;
//		if(Blue_data[0]==108&&Blue_data[1]==108)Sign=5;
//		if(Blue_data[0]==102&&Blue_data[1]==102)Sign=1;
//		if(Blue_data[0]==97&&Blue_data[1]==97)Sign=2;
//		if((Blue_data[0]==108&&Blue_data[1]==115)||(Blue_data[0]==115&&Blue_data[1]==108))Sign=3;
//		if((Blue_data[0]==114&&Blue_data[1]==115)||(Blue_data[0]==115&&Blue_data[1]==114))Sign=4;
//		if(Blue_data[0]==114&&Blue_data[1]==114)Sign=6;
//		if((Blue_data[0]==108&&Blue_data[1]==117)||(Blue_data[0]==117&&Blue_data[1]==108))Sign=7;
//		if((Blue_data[0]==114&&Blue_data[1]==117)||(Blue_data[0]==117&&Blue_data[1]==114))Sign=9;
//		if((Blue_data[0]==108&&Blue_data[1]==100)||(Blue_data[0]==100&&Blue_data[1]==108))Sign=8;
//		if(Blue_data[0]==112&&Blue_data[1]==112)//PP
//		{
//			bug=0;
//			Sign=12;
//			Sign1++;
//		}
////		sprintf((char *)string,"%d",Blue_data[0]);
////		OLED_ShowString(0,0,string,8);
////		sprintf((char *)string,"%d",Blue_data[1]);
////		OLED_ShowString(0,16,string,8);
////		sprintf((char *)string,"%d",Blue_data[2]);
////		OLED_ShowString(0,32,string,8);
////		sprintf((char *)string,"%d",Blue_data[3]);
////		OLED_ShowString(0,48,string,8);
////		OLED_Update();
//	}
}
