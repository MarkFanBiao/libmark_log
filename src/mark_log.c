#include "mark_log.h"

Mark_Log_Ctl mk_ctl = {NULL};

void mark_create(void)
{
    mk_ctl.markfp = fopen(LOG_DIR, "a+");
    if(NULL == mk_ctl.markfp)
    {
        perror("fopen");
        return;
    }
}

static inline void getNowTime(char *timeStr, size_t len)
{
    time_t rawtime;
    struct tm tmnow;
    rawtime = time(NULL);
    localtime_r(&rawtime, &tmnow);
    snprintf(timeStr, len, "%04d-%02d-%02d %02d:%02d:%02d",
             tmnow.tm_year+1900, tmnow.tm_mon+1, tmnow.tm_mday,
             tmnow.tm_hour, tmnow.tm_min, tmnow.tm_sec);
}

static inline void getLogLevel(char *levelStr, size_t len, mark_level level)
{
    switch (level) {
    case MARK_NOTICE:
        strncpy(levelStr, "NOTICE", len);
        break;
    case MARK_DEBUG:
        strncpy(levelStr, "DEBUG", len);
        break;
    case MARK_WARNING:
        strncpy(levelStr, "WARNING", len);
        break;
    case MARK_ERROR:
        strncpy(levelStr, "ERROR", len);
        break;
    default:
        break;
    }
}

void __mark_log(char *file, int line, mark_level level, const char *fmt, ...)
{
    char timebuf[20];   //2018-08-08 17:48:30
    char levelString[16];

    va_list ap;
    va_start(ap, fmt);

    getNowTime(timebuf, sizeof(timebuf));
    getLogLevel(levelString, sizeof(levelString), level);
    fprintf(mk_ctl.markfp, "[%s]-[%s]-[%s: line %d]: ",
            timebuf, levelString, file, line);
    vfprintf(mk_ctl.markfp, fmt, ap);
    va_end(ap);
    fflush(mk_ctl.markfp);
}
void mark_clean(void)
{
    if(NULL != mk_ctl.markfp)
    {
        fclose(mk_ctl.markfp);
    }
}
