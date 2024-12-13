#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

char *getTimeNow()
{
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char *time_buffer = (char *)malloc(20);
    if (time_buffer == NULL)
    {
        return NULL;
    }
    strftime(time_buffer, 20, "%Y-%m-%d %H:%M:%S", tm_info);
    return time_buffer;
}
