#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_
#include "sys.h"
#include "OLED.h"
#include "OLED_Content.h"
#include "OLED_Data.h"
#include "led.h"
#include "infrared.h"
#include "mode.h"
#include "usart.h"

void USART3_Init(u32 baud);

extern u8 Sign1;
extern int USART3_Sign;
extern volatile uint8_t jdy_at_mode;
extern volatile uint8_t bt_data_ready;

/* JDY-23 AT指令功能 */
extern char JDY_MAC_Str[18];        // 存储MAC地址字符串 "XX:XX:XX:XX:XX:XX"
extern volatile uint8_t jdy_at_done; // AT指令响应完成标志

void JDY_SendString(const char *str);
void JDY_SendATCommand(const char *cmd);
void JDY_QueryMAC(void);

#endif
