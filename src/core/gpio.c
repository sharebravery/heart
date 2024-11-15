#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "gpio.h"
#include "logger.h"
#include <common.h>
#include "utils.h"

int gpio_init()
{
    int fd = open("/sys/class/gpio/export", O_WRONLY);

    if (fd < 0)
    {
        return -1;
    }

    return 0;
}

int gpio_main()
{
    const char *message = "This is a test log message";

    log_error("START....%s", message);
    log_info("START....%s", message);
    return 0;
}