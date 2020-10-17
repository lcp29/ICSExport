
/* output.c
 * 读取相关变量并将ics输出到缓冲区
 */

#include "defs.h"

void printHead()
{
    sprintf(obuf + pObuf, "BEGIN:VCALENDAR\n"
                          "PRODID:-//lcp29//icsexport\n"
                          "VERSION:2.0\n"
                          "METHOD:PUBLISH\n"
                          "BEGIN:TIMEZONE\n"
                          "TZID:Asia/Shanghai\n"
                          "BEGIN:STANDARD\n"
                          "DTSTART:16000101T000000\n"
                          "TZOFFSETFROM:+0800\n"
                          "TZOFFSETTO:+0800\n"
                          "END:STANDARD\n"
                          "END:TIMEZONE\n");
    pObuf = strlen(obuf);
    return;
}

void printTail()
{
    sprintf(obuf + pObuf, "END:VCALENDAR\n");
    pObuf = strlen(obuf);
    return;
}

void printVEvent(VEVENT *vEvent)
{
    char uid[UID_LENGTH + 1];
    char dtend[16];
    char dtstart[16];
    int rcnt = 0;
    for (int d = 0; d < vEvent->dtn; ++d) //Token日期
    {
        if (vEvent->DATETOKEN[d].type == 1)
            evalNthMonday(dtstart, vEvent->DATETOKEN[d].b);
        else
        {
            evalNthMonday(dtstart, vEvent->DATETOKEN[d].be[0]);
            rcnt = vEvent->DATETOKEN[d].be[1] - vEvent->DATETOKEN[d].be[0] + 1;
        }
        for (int w = 0; w < vEvent->wtn; ++w) //Token周几上
        {
            for (int i = 1; i < vEvent->WTOKEN[w].b; ++i) //WTOKEN的type一定是1，不用检查
                nextDay(dtstart, dtstart);
            strncpy(dtend, dtstart, 8);
            for (int t = 0; t < vEvent->ttn; ++t) //Token时间
            {
                genUID(uid);
                dtstart[8] = 'T';
                dtend[8] = 'T';
                if (vEvent->TIMETOKEN[t].type == 1)
                {
                    strncpy(dtstart + 9, clses[vEvent->TIMETOKEN[t].b - 1].CBEGIN, 6);
                    strncpy(dtend + 9, clses[vEvent->TIMETOKEN[t].b - 1].CEND, 6);
                }
                else
                {
                    strncpy(dtstart + 9, clses[vEvent->TIMETOKEN[t].be[0] - 1].CBEGIN, 6);
                    strncpy(dtend + 9, clses[vEvent->TIMETOKEN[t].be[1] - 1].CEND, 6);
                }
                sprintf(obuf + pObuf, "BEGIN:VEVENT\n"
                                      "CLASS:PUBLIC\n"
                                      "DTSTAMP:%s\n"
                                      "UID:%s\n"
                                      "SUMMARY:%s\n"
                        "DTEND;TZID=Asia/Shanghai:%s\n"
                        "DTSTART;TZID=Asia/Shanghai:%s\n",
                        vEvent->DTSTAMP,
                        uid,
                        vEvent->SUMMARY,
                        dtend,
                        dtstart);
                pObuf = strlen(obuf);
                if (vEvent->DATETOKEN[d].type == 2)
                {
                    sprintf(obuf + pObuf, "RRULE:FREQ=WEEKLY;COUNT=%d\n", rcnt);
                    pObuf = strlen(obuf);
                }
                sprintf(obuf + pObuf, "LOCATION:%s\n"
                                      "DESCRIPTION:%s\n"
                                      "TRANSP:OPAQUE\n"
                                      "END:VEVENT\n",
                        vEvent->LOCATION,
                        vEvent->DESCRIPTION);
                pObuf = strlen(obuf);
            }
        }
    }
    return;
}
