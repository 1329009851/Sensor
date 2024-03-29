#include "key.h"

bool readKey(int sw)
{
  if (digitalRead(sw))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


uint8_t keyDetect(int sw)
{
  static uint8_t duriation;  // 用于在等待状态中计数

  switch (keyState)
  {
    case KEY_STATE_RELEASE:
      if (readKey(sw) == 1)    // 如果按键按下
      {
        keyState = KEY_STATE_WAITING;  // 转换至下一个状态
      }
      return NOT_PRESSED;    // 返回：按键未按下
      break;

    case KEY_STATE_WAITING:
      if (readKey(sw) == 1)    // 如果按键按下
      {
        duriation++;
        if (duriation >= PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
        { // 说明没有抖动了，可以确定按键已按下
          duriation = 0;
          keyState = KEY_STATE_LONG_PRESSED;  // 转换至下一个状态
          return PRESSED;
        }
      }
      else  // 如果此时按键松开
      { // 可能存在抖动或干扰
        duriation = 0;  // 清零的目的是便于下次重新计数
        keyState = KEY_STATE_RELEASE;  // 重新返回按键松开的状态
        return NOT_PRESSED;
      }
      break;

    case KEY_STATE_LONG_PRESSED:
      if (readKey(sw) == 1)
      {
        duriation++;
        if (duriation >= LONG_PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
        {
          duriation = 0;
          keyState = KEY_STATE_LONG_PRESSED;  // 转换至下一个状态
          return PRESSED;
        }
      }
      else
      {
        duriation = 0;
        keyState = KEY_STATE_PRESSED;
        return PRESSED;
      }
      break;


    case KEY_STATE_PRESSED:
      if (readKey(sw) == 0)      // 如果按键松开
      {
        keyState = KEY_STATE_RELEASE;  // 回到按键松开的状态
      }
      return NOT_PRESSED;
      break;

    default:
      keyState = KEY_STATE_RELEASE;
      return NOT_PRESSED;
      break;
  }
}
