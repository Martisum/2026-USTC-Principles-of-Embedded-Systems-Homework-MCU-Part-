#ifndef OLED_DEBUG_H
#define OLED_DEBUG_H

#include "OLED.h"

/* 调试信息数组：8行，每行最多31个字符（+1个'\0'结束符） */
#define OLED_DEBUG_ROWS    8
#define OLED_DEBUG_COLS    32

extern char OLED_Debug_mesg[OLED_DEBUG_ROWS][OLED_DEBUG_COLS];
extern char OLED_Debug_str[OLED_DEBUG_COLS];

/* 初始化调试显示 */
void OLED_Debug_Init(void);

/* 滚动刷新：添加新消息到底部，旧消息上移一行，并刷新OLED显示 */
void OLED_Debug_Scroll(const char *new_msg);

/* 将当前调试数组全部显示到OLED上 */
void OLED_Debug_Show(void);

#endif
