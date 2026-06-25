#include "OLED.h"
#include "OLED_Debug.h"
#include <string.h>

/* 调试信息二维数组：8行 × 32列（每行最多31个有效字符 + 结束符） */
char OLED_Debug_mesg[OLED_DEBUG_ROWS][OLED_DEBUG_COLS] = {0};
char OLED_Debug_str[OLED_DEBUG_COLS] = {0};

/**
  * @brief  初始化调试显示模块
  * @note   清空调试数组和OLED屏幕
  */
void OLED_Debug_Init(void)
{
    uint8_t i;
    for (i = 0; i < OLED_DEBUG_ROWS; i++)
    {
        OLED_Debug_mesg[i][0] = '\0';
    }
    OLED_Clear();
    OLED_DisplayFlip(OLED_FLIP_180); // 确保OLED显示为正常方向
    OLED_Update();
}

/**
  * @brief  滚动刷新：将新消息添加到底部，已有的消息全部上移一行
  * @param  new_msg  要显示的新调试信息字符串（超过31字符会被截断）
  * @note   调用后会立即刷新OLED显示
  */
void OLED_Debug_Scroll(const char *new_msg)
{
    uint8_t i;

    /* 将所有行向上滚动一行（第0行被挤出，第1行→第0行，...，第7行→第6行） */
    for (i = 0; i < OLED_DEBUG_ROWS - 1; i++)
    {
        strncpy(OLED_Debug_mesg[i], OLED_Debug_mesg[i + 1], OLED_DEBUG_COLS - 1);
        OLED_Debug_mesg[i][OLED_DEBUG_COLS - 1] = '\0';
    }

    /* 将新消息写入最后一行 */
    if (new_msg != NULL)
    {
        strncpy(OLED_Debug_mesg[OLED_DEBUG_ROWS - 1], new_msg, OLED_DEBUG_COLS - 1);
    }
    else
    {
        OLED_Debug_mesg[OLED_DEBUG_ROWS - 1][0] = '\0';
    }
    OLED_Debug_mesg[OLED_DEBUG_ROWS - 1][OLED_DEBUG_COLS - 1] = '\0';

    /* 刷新OLED显示 */
    OLED_Debug_Show();
}

/**
  * @brief  将OLED_Debug_mesg数组的全部内容显示到OLED屏幕上
  * @note   使用6x8字体，每行高度8像素，8行正好占满64像素高的屏幕
  */
void OLED_Debug_Show(void)
{
    uint8_t i;

    OLED_Clear();
    for (i = 0; i < OLED_DEBUG_ROWS; i++)
    {
        /* Y坐标 = 行号 × 8（6x8字体每行占8像素高） */
        OLED_ShowString(0, i * 8, OLED_Debug_mesg[i], OLED_6X8);
    }
    OLED_Update();
}
