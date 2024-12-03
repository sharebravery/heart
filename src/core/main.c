#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "gpio.h"

int pin = 21; // 假设 GPIO 21

// 信号处理函数
void cleanup_gpio(int signo)
{
    if (gpio_deinit(pin) == 0)
    {
        printf("GPIO %d successfully unexported.\n", pin);
    }
    else
    {
        fprintf(stderr, "Failed to unexport GPIO %d.\n", pin);
    }
    exit(0);
}

int main()
{
    // 注册信号处理程序
    signal(SIGINT, cleanup_gpio);  // 捕获 Ctrl+C
    signal(SIGTERM, cleanup_gpio); // 捕获 kill 命令

    // 初始化为输出模式
    if (gpio_init(pin, GPIO_MODE_OUTPUT) < 0)
    {
        fprintf(stderr, "Failed to initialize GPIO.\n");
        return 1;
    }

    // 循环设置高低电平
    for (int i = 0; i < 10; i++)
    {
        gpio_write(pin, GPIO_HIGH);
        printf("GPIO %d set to HIGH\n", pin);
        sleep(1);

        gpio_write(pin, GPIO_LOW);
        printf("GPIO %d set to LOW\n", pin);
        sleep(1);
    }

    // 程序正常退出时也要清理 GPIO
    gpio_deinit(pin);

    return 0;
}
