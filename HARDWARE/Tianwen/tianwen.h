#ifndef __TIANWEN_H
#define __TIANWEN_H	 
#include "sys.h"
#include "OLED.h"
#include "OLED_Data.h"
#include "OLED_Content.h"
#include "mode.h"

extern u16 USART2_Res;
extern int USART2_Sign;
extern int Sign;

void USART2_Init(u32 baud);

		 				    
#endif
