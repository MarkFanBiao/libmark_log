#ifndef _MARK_LOG_H
#define _MARK_LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

typedef enum _mark_level{
    MARK_NOTICE,
    MARK_DEBUG,
    MARK_WARNING,
    MARK_ERROR
}mark_level;

typedef struct _Mark_Log_Ctl
{
    FILE *markfp;
}Mark_Log_Ctl;

#define LOG_DIR "/home/mark/mark_log.1.0.1/logdir/log_demo"
#define MARK_LOG(level,fmt,...) __mark_log(__FILE__, __LINE__, level, fmt, ##__VA_ARGS__)

void mark_create(void);
void __mark_log(char *file, int line, mark_level level, const char *fmt, ...);
void mark_clean(void);

#endif
