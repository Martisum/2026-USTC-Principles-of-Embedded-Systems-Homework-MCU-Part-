#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#include "sys.h"
#include "OLED.h"
#include "OLED_Content.h"
#include "OLED_Data.h"
#include "led.h"
#include "infrared.h"
#include "mode.h"

void USART3_Init(u32 baud);

extern u8 Sign1;
extern int USART3_Sign;


#endif
