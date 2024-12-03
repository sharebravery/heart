#include "gpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static int platform_supports_sysfs_gpio()
{
    return access("/sys/class/gpio/export", F_OK) == 0;
}

static int sysfs_export(int pin)
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);

    if (fd < 0)
    {
        return -1;
    }
    close(fd);
    return 0;
}

static int sysfs_unexport(int pin)
{
    int fd = open("/sys/class/gpio/unexport", O_WRONLY);

    if (fd < 0)
    {
        return -1;
    }
    close(fd);
    return 0;
}

static int sysfs_set_direction(int pin, GPIO_Mode mode)
{
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    int fd = open(path, O_WRONLY);

    if (fd < 0)
    {
        return -1;
    }

    if (mode == GPIO_MODE_OUTPUT)
    {
        write(fd, "out", 4);
    }
    else
    {
        write(fd, "in", 3);
    }

    close(fd);

    return 0;
}

static int sysfs_write(int pin, GPIO_State state)
{
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(path, O_WRONLY);

    if (fd < 0)
    {
        return -1;
    }

    close(fd);
    return 0;
}

static GPIO_State sysfs_read(int pin)
{
    char path[64];
    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return GPIO_LOW;
    int value = 0;
    close(fd);
    return value == 1 ? GPIO_HIGH : GPIO_LOW;
}

int gpio_init(int pin, GPIO_Mode mode)
{
    if (!platform_supports_sysfs_gpio())
    {
        fprintf(stderr, "Platform does not support sysfs GPIO.\n");
        return -1;
    }
    if (sysfs_export(pin) < 0)
    {
        fprintf(stderr, "Failed to export GPIO %d.\n", pin);
        return -1;
    }

    if (sysfs_set_direction(pin, mode) < 0)
    {
        fprintf(stderr, "Failed to set GPIO %d direction.\n", pin);
        return -1;
    }

    return 0;
}

int gpio_write(int pin, GPIO_State state)
{
    if (sysfs_write(pin, state) < 0)
    {
        fprintf(stderr, "Failed to write GPIO %d.\n", pin);
        return -1;
    }
    return 0;
}

GPIO_State gpio_read(int pin)
{
    return sysfs_read(pin);
}

int gpio_deinit(int pin)
{
    if (sysfs_unexport(pin) < 0)
    {
        fprintf(stderr, "Failed to unexport GPIO %d.\n", pin);
        return -1;
    }
    return 0;
}
