/*
 * proc.c
 * 处理脚本内容
 */

#include "defs.h"

void readHead()
{
    int wcnt;
    char mon[9];
    readNextUnannoedUnemptyLine();      //                              标准脚本格式：
    sscanf(lbuf, "%d-%8s", &wcnt, mon); //                              6-20201012
    evalFirstMonday(wcnt, mon);
    readNextUnannoedUnemptyLine();
    sscanf(lbuf, "%d", &numOfClasses); //                               6
    clses = (struct CNUM *)malloc(sizeof(struct CNUM) * numOfClasses);
    for (int i = 0; i < numOfClasses; ++i) //                           083000-101500
    {                                      //                           103000-121500
        readNextUnannoedUnemptyLine();     //                           ...
        sscanf(lbuf, "%6s-%6s", clses[i].CBEGIN, clses[i].CEND);
    }
    return;
}

void freeMem()
{
    free(clses);
    return;
}
