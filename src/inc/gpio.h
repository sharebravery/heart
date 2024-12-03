#ifndef GPIO_H
#define GPIO_H

// 定义 GPIO 方向和状态
typedef enum
{
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT
} GPIO_Mode;

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH = 1
} GPIO_State;

// 初始化 GPIO 引脚
int gpio_init(int pin, GPIO_Mode mode);

// 写入 GPIO 状态
int gpio_write(int pin, GPIO_State state);

// 读取 GPIO 状态
GPIO_State gpio_read(int pin);

// 释放 GPIO 引脚
int gpio_deinit(int pin);

#endif
