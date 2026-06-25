#include "mode.h"

u16 count=0;

//1号脚--->左前
//2号脚--->右后
//3号脚--->右前
//4号脚--->左后

u8 bug = 0;//解决前进后退刚开始的步态适应

/**
  * 函    数：动作延时函数
  * 参    数：x是初始值，y是要到达的值，num是通道号
  * 返 回 值：无
  */
void For(int x,int y,int num)
{
	int i,sign;
	if(x>y)sign=1;
	if(y>x)sign=0;
	if(num==1)//通道1
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare1(TIM4,i);
				delay_us(100);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare1(TIM4,i);
				delay_us(100);
			}
		}
	}
	if(num==2)//通道3
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare2(TIM4,i);
				delay_us(100);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare2(TIM4,i);
				delay_us(100);
			}
		}
	}
	if(num==3)//通道3
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare3(TIM4,i);
				delay_us(100);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare3(TIM4,i);
				delay_us(100);
			}
		}
	}
	if(num==4)//通道4
	{
		if(sign==1)
		{
			for(i=x;i>=y;i--)
			{
				TIM_SetCompare4(TIM4,i);
				delay_us(100);
			}
		}
		else if(sign==0)
		{
			for(i=x;i<=y;i++)
			{
				TIM_SetCompare4(TIM4,i);
				delay_us(100);
			}
		}
	}
}




void Stand(void)//站立
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP1);
	OLED_Update();
	TIM_SetCompare1(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,150 );//占空比7.5%旋转90度
	
	while(1)
	{
		count++;
		delay_ms(1);
		if(count%2==0)//摇尾巴函数 
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void Rock(void)//摇摆
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP9);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		
		if(count==150)
		{
			For(180,120,1);
			For(120,180,2);
			For(120,180,3);
			For(180,120,4);
		}
		if(count==350)
		{
			For(120,180,1);
			For(180,120,2);
			For(180,120,3);
			For(120,180,4);
		}
		if(count>=370)
		{
			count=0;
			break;
		}
	}
}

void Handshake(void)//握手
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP11);
	OLED_Update();
	TIM_SetCompare2(TIM4,220 );
	TIM_SetCompare3(TIM4,160 );
	TIM_SetCompare4(TIM4,140 );
	while(1)
	{
		delay_ms(1);
		count++;
		
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		
		if(count==200)
		{
			For(115,55,1);
		}
		if(count==500)
		{
			For(55,115,1);
		}
		if(count>=550)
		{
			count=0;
			break;
		}
	}
}



void Sleep(void)//睡觉
{
	OLED_ShowImage(0,0,128,64,BMP6);
	OLED_Update();
	TIM_SetCompare1(TIM4,70 );
	TIM_SetCompare2(TIM4,70 );
	TIM_SetCompare3(TIM4,225 );
	TIM_SetCompare4(TIM4,225 );
}

void Sit(void)//坐
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP10);
	OLED_Update();
	TIM_SetCompare1(TIM4,85 );
	TIM_SetCompare2(TIM4,215 );
	TIM_SetCompare3(TIM4,215 );
	TIM_SetCompare4(TIM4,85 );
	
	while(1)
	{
		count++;
		delay_ms(1);
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		if(count==600)
		{
			count=0;
			break;
		}
	}
}



void Advance(void)//前进
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		if(count==50&&bug==0)
		{
			For(150,150,1);
			For(150,150,2);
		}
		if(count==50&&bug!=0)
		{
			For(150,195,1);
			For(150,105,2);
		}
		if(count==200)
		{
			For(105,150,4);
			For(195,150,3);
		}
		if(count==350&&bug==0)
		{
			For(150,105,1);
			For(150,195,2);
		}
		if(count==350&&bug!=0)
		{
			For(195,105,1);
			For(105,195,2);
		}
		if(count==550)
		{
			For(150,195,4);
			For(150,105,3);
		}
		if(count==700)
		{
			For(105,150,1);
			For(195,150,2);
		}
		if(count==900)
		{
			For(195,105,4);
			For(105,195,3);
		}

		if(count>=920)
		{
			count=0;
			break;
		}
	}
}

void Queen(void)//后退
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP2);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		if(count==50&&bug==0)
		{
			For(150,150,1);
			For(150,150,2);
		}
		if(count==50&&bug!=0)
		{
			For(150,115,1);
			For(150,185,2);
		}
		if(count==200)
		{
			For(185,150,4);
			For(115,150,3);
		}
		if(count==350&&bug==0)
		{
			For(150,185,1);
			For(150,115,2);
		}
		if(count==350&&bug!=0)
		{
			For(115,185,1);
			For(185,115,2);
		}
		if(count==550)
		{
			For(150,115,4);
			For(150,185,3);
		}
		if(count==700)
		{
			For(185,150,1);
			For(115,150,2);
		}
		if(count==900)
		{
			For(115,185,4);
			For(185,115,3);
		}
		if(count>=920)
		{
			count=0;
			break;
		}
	}
}

void Right(void)//右转
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP3);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		
		if(count==50)
		{
			For(150,105,1);
			For(150,105,2);
		}
		if(count==200)
		{
			For(150,195,4);
			For(150,195,3);
		}
		if(count==350)
		{
			For(105,150,1);
			For(105,150,2);
		}
		if(count==500)
		{
			For(195,150,4);
			For(195,150,3);
		}
		if(count>=550)
		{
			count=0;
			break;
		}
	}
}

void Left(void)//左转
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP4);
	OLED_Update();

	while(1)
	{
		count++;
		delay_ms(1);
		
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		

		if(count==50)
		{
			For(150,195,4);
			For(150,195,3);
		}
		if(count==200)
		{
			For(150,105,1);
			For(150,105,2);
		}
		if(count==350)
		{
			For(195,150,4);
			For(195,150,3);
		}
		if(count==500)
		{
			For(105,150,1);
			For(105,150,2);
		}
		if(count>=550)
		{
			count=0;
			break;
		}
	}
}

void pee(void)//撒尿
{
	int j=0,sign=0;
	
	TIM_SetCompare1(TIM4,150 );//占空比7.5%旋转90度
	TIM_SetCompare2(TIM4,50 );//占空比7.5%旋转90度
	TIM_SetCompare3(TIM4,130 );//占空比7.5%旋转90度
	TIM_SetCompare4(TIM4,170 );//占空比7.5%旋转90度
	
	OLED_ShowImage(0,0,128,64,BMP9);
	OLED_Update();
	
	while(1)
	{
		count++;
		delay_ms(1);
		if(count%2==0)//摇尾巴函数 
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		if(count==600)
		{
			count=0;
			break;
		}
	}
}

void dance(void)//跳舞
{
	int j=0,sign=0;
	
	OLED_ShowImage(0,0,128,64,BMP11);
	OLED_Update();

	while(1)
	{
		count++;
		delay_ms(1);
		
		if(count%2==0)
		{
			j++;
			if(sign%2!=0)
			{
				TIM_SetCompare1(TIM3,(100+j));
			}
			if(sign%2==0)
			{
				TIM_SetCompare1(TIM3,(200-j));
			}
			if(j==100)
			{
				sign++;
				j=0;
			}
		}
		
		if(count==50)
		{
			For(150,90,1);
			For(150,90,2);
			For(150,90,3);
			For(150,90,4);
		}
		if(count==200)
		{
			For(90,150,1);
			For(90,150,2);
			For(90,150,3);
			For(90,150,4);
		}
		if(count==350)
		{
			For(150,210,1);
			For(150,210,2);
			For(150,210,3);
			For(150,210,4);
		}
		if(count==500)
		{
			For(210,150,1);
			For(210,150,2);
			For(210,150,3);
			For(210,150,4);
		}
		if(count==650)
		{
			For(150,105,1);
			For(150,195,2);
			For(150,195,3);
			For(150,105,4);
		}
		if(count==800)
		{
			For(105,150,1);
			For(195,150,2);
			For(195,150,3);
			For(105,150,4);
		}
		if(count==950)
		{
			For(150,195,1);
			For(150,105,2);
			For(150,105,3);
			For(150,195,4);
		}
		if(count==1100)
		{
			For(195,150,1);
			For(105,150,2);
			For(105,150,3);
			For(195,150,4);
		}
		if(count==1250)
		{
			For(150,195,1);
			For(150,105,2);
			For(150,105,3);
			For(150,195,4);
		}
		if(count==1400)
		{
			For(195,150,1);
			For(105,150,2);
			For(105,150,3);
			For(195,150,4);
		}
		if(count==1550)
		{
			For(150,105,1);
			For(150,195,2);
			For(150,195,3);
			For(150,105,4);
		}
		if(count==1700)
		{
			For(105,150,1);
			For(195,150,2);
			For(195,150,3);
			For(105,150,4);
		}
		if(count==1850)
		{
			For(150,90,1);
			For(150,90,2);
		}
		if(count==2000)
		{
			For(90,150,1);
			For(90,150,2);
		}
		if(count==2150)
		{
			For(150,210,3);
			For(150,210,4);
		}
		if(count==2300)
		{
			For(210,150,3);
			For(210,150,4);
		}
		if(count>=2350)
		{
			count=0;
			break;
		}
	}
}
