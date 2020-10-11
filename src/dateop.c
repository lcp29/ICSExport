
/*
 * dateop.c
 * 日期相关操作
 */

#include "defs.h"

int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void evalFirstMonday(int weekcnt, const char *monOfThis)
{
    strncpy(firstMonday, monOfThis, 8);
    for (int i = 1; i < weekcnt; ++i)
        lastWeek(firstMonday, firstMonday);
    return;
}

void nextDay(const char *now, char *next)
{
    char yyyy[5], MM[3];
    strncpy(yyyy, now, 4);
    strncpy(MM, now + 4, 2);
    int y, M, d;
    y = atoi(yyyy);
    M = atoi(MM);
    d = atoi(now + 6);
    if (isLeapYear(y))
        daysInMonths[1] = 29;
    else
        daysInMonths[1] = 28;
    if (++d > daysInMonths[M - 1])
    {
        d = 1;
        if (++M > 12)
        {
            M = 1;
            ++y;
        }
    }
    sprintf(next, "%04d", y);
    sprintf(next + 4, "%02d", M);
    sprintf(next + 6, "%02d", d);
    return;
}

void lastDay(const char *now, char *last)
{
    char yyyy[5], MM[3];
    strncpy(yyyy, now, 4);
    strncpy(MM, now + 4, 2);
    int y, M, d;
    y = atoi(yyyy);
    M = atoi(MM);
    d = atoi(now + 6);
    if (isLeapYear(y))
        daysInMonths[1] = 29;
    else
        daysInMonths[1] = 28;
    if (--d < 1)
    {
        if (--M < 1)
        {
            M = 12;
            --y;
        }
        d = daysInMonths[M - 1];
    }
    sprintf(last, "%02d", y);
    sprintf(last + 4, "%02d", M);
    sprintf(last + 6, "%02d", d);
    return;
}

int isLeapYear(int now)
{
    return (now % 4 == 0 && (now % 100 != 0 || now % 400 == 0)) ? 1 : 0;
}

void nextWeek(const char *now, char *next)
{
    strncpy(next, now, 8);
    for (int i = 1; i <= 7; ++i)
        nextDay(next, next);
    return;
}

void lastWeek(const char *now, char *last)
{
    strncpy(last, now, 8);
    for (int i = 1; i <= 7; ++i)
        lastDay(last, last);
    return;
}
