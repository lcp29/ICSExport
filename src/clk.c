/*
 * clk.c
 * 处理时钟和随机数
 */

#include "defs.h"

void genGmStamp(char *stamp)
{
    time_t rawTime;
    struct tm *gmt = NULL;
    time(&rawTime);
    rawTime -= TIMEZONE;
    gmt = gmtime(&rawTime);
    strftime(stamp, 17, "%Y%m%dT%H%M%SZ", gmt);
    return;
}

void genUID(char *uid)
{
    const char *chs = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i <= UID_LENGTH - 1; ++i)
        uid[i] = chs[rand() % 62];
    return;
}

void randInit()
{
    srand(time(NULL));
    return;
}
