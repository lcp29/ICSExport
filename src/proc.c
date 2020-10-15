/*
 * proc.c
 * 处理脚本内容
 */

#include "defs.h"

void readHead()
{
    int wcnt;
    char mon[9];
    readNextUnannoedUnemptyLine();                       //      标准脚本格式：
    sscanf(lbuf, "%d-%8s", &wcnt, mon);                  //     | 6-20201012
    evalFirstMonday(wcnt, mon);                          //     |
    readNextUnannoedUnemptyLine();                       //     |
    sscanf(lbuf, "%d", &numOfClasses);                   //     | 6
    clses = (CNUM *)malloc(sizeof(CNUM) * numOfClasses); //     |
    for (int i = 0; i < numOfClasses; ++i)               //     | 083000-101500
    {                                                    //     | 103000-121500
        readNextUnannoedUnemptyLine();                   //     | ...
        sscanf(lbuf, "%6s-%6s", clses[i].CBEGIN, clses[i].CEND);
    }
    return;
}

void freeMem()
{
    for (int i = 0; i < numOfEvents; ++i)
    {
        free(events[i].DATETOKEN);
        free(events[i].TIMETOKEN);
    }
    free(clses);
    free(events);
    return;
}

void readBody()
{
    char dts[MAX_TBUF_SIZE];
    char tts[MAX_TBUF_SIZE];
    readNextUnannoedUnemptyLine();                  //  | ...
    sscanf(lbuf, "%d", &numOfClasses);              //  | 18
    events = malloc(sizeof(VEVENT) * numOfClasses); //  |
    for (int i = 0; i < numOfClasses; i++)          //  |
    {                                               //  |
        readNextUnannoedUnemptyLine();              //  |
        sscanf(lbuf, "%s", events[i].SUMMARY);      //  | 高等数学
        readNextUnannoedUnemptyLine();              //  |
        sscanf(lbuf, "%s", events[i].DESCRIPTION);  //  | 陈国延
        readNextUnannoedUnemptyLine();              //  |
        sscanf(lbuf, "%s", events[i].DESCRIPTION);  //  | T3201
        readNextUnannoedUnemptyLine();              //  |
        sscanf(lbuf, "%s", dts);                    //  | 3-7，9
        readNextUnannoedUnemptyLine();              //  |
        sscanf(lbuf, "%s", tts);                    //  | 2
        //解释日期和时间并存入events
        events[i].DATETOKEN = genToken(dts, &events[i].dtn);
        events[i].TIMETOKEN = genToken(tts, &events[i].ttn);
        //生成UID和时间戳
        genGmStamp(events[i].DTSTAMP);
        genUID(events[i].UID);
    }
    return;
}

void clsNoToClsTime(char *start, char *end)
{
    //lbuf已有所需内容
    int a;
    char cns[4], cne[4];
    for (a = 0; lbuf[a] >= '0' && lbuf[a] <= '9'; ++a)
        ;
    strncpy(cns, lbuf, a + 1);
    if (lbuf[a] == '\0')
        strcpy(cne, cns); //安全
    else if (lbuf[a] == '-')
        strcpy(cne, lbuf + a + 1); //安全
    int cnsi = atoi(cns);
    int cnei = atoi(cne);
    strcpy(start, clses[cnsi - 1].CBEGIN);
    strcpy(end, clses[cnei - 1].CEND);
    return;
}
