#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "logger.h"
#include "common.h"
#include "utils.h"

void log_error(const char *fmt, ...)
{
    va_list args;
    char buffer[256];

    char *currentTime = getTimeNow();

    fprintf(stderr, "%s[%s] ERROR: ", COLOR_RED, currentTime);

    va_start(args, fmt);

    vsnprintf(buffer, sizeof(buffer), fmt, args);

    fprintf(stderr, "%s%s\n", COLOR_RED, buffer);

    va_end(args);
}

void log_info(const char *fmt, ...)
{
    va_list args;
    char buffer[256];

    char *currentTime = getTimeNow();

    fprintf(stderr, "%s[%s] INFOM: ", COLOR_BLUE, currentTime);

    va_start(args, fmt);

    vsnprintf(buffer, sizeof(buffer), fmt, args);

    fprintf(stderr, "%s%s\n", COLOR_BLUE, buffer);

    va_end(args);
}
