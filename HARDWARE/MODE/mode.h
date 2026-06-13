#ifndef __MODE_H
#define __MODE_H	 
#include "sys.h"
#include "delay.h"
#include "infrared.h"
#include "tianwen.h"

extern u16 count;
extern u8 bug;

void Stand(void);//站立
void Advance(void);//前进
void Queen(void);//后退
void Left(void);//左转
void Right(void);//右转
void Rock(void);//摇摆
void Sleep(void);//睡觉
void Sit(void);//坐
void Handshake(void);//握手
void pee(void);//撒尿
void dance(void);//跳舞
void mode(void);

void For(int x,int y,int num);
		 				    
#endif
