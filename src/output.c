
/* output.c
 * 读取相关变量并将ics输出到缓冲区
 */

#include "defs.h"

void printHead()
{
    obuf[0] = '\0';
    sprintf(obuf, "BEGIN:VCALENDAR\n"
                  "PRODID:-//lcp29//icsexport\n"
                  "VERSION:2.0\n"
                  "METHOD:PUBLISH\n"
                  "BEGIN:TIMEZONE\n"
                  "TZID:Asia/Shanghai\n"
                  "BEGIN:STANDARD\n"
                  "DTSTART:16000101T000000\n"
                  "TZOFFSETFROM:+0800\n"
                  "TZOFFSETTO:+0800"
                  "END:STANDARD\n"
                  "END:TIMEZONE");
    return;
}
