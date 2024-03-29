#include "Arduino.h"
#include "system.h"

/* 按键去抖动状态机中的三个状态 */
#define KEY_STATE_RELEASE   0 // 按键未按下
#define KEY_STATE_WAITING   1 // 等待（消抖）
#define KEY_STATE_PRESSED   2 // 按键按下（等待释放）
#define KEY_STATE_LONG_PRESSED   3

/* 等待状态持续时间
  需要根据单片机速度和按键消抖程序被调用的速度来进行调整
*/
#define PRESSED_TIME 40
#define LONG_PRESSED_TIME 255

/* 按键检测函数的返回值，按下为 1，未按下为 0 */
#define LONG_PRESSED 2
#define PRESSED 1
#define NOT_PRESSED 0

/* 按键扫描程序所处的状态
  初始状态为：按键按下（KEY_STATE_RELEASE）
*/
extern uint8_t keyState;

bool readKey(int sw);
uint8_t keyDective(int sw);
