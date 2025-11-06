#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "log.h"

void log_message(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    time_t current_time = time(NULL);
    struct tm* t = localtime(&current_time);
    char time_buf[20];
    strftime(time_buf, sizeof(time_buf), "%H:%M:%S", t);
    printf("[%s] ", time_buf);

    vprintf(fmt, args);

    fflush(stdout);
    
    va_end(args);

}