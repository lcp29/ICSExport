/*
 * icsexport.c
 * .ics课表导出工具
 * 
 * 一些解释需要参阅./doc/软件维护手册.md
 * 引用格式：SM<对应章节>
 * 
 */

#include "defs.h"

int main(int argc, char *argv[])
{
    //开始阶段
    randInit();
    readArguments(argc, argv);
    argFlagDealer();
    if (argFlag & ABORT)
        return 0;
    //读取文件
    openScript();
    fileFlagDealer();
    if (fileFlag & ABORT)
        return 0; //是安全的
    readHead();
    readBody();
    //打印输出
    printHead();
    for (int i = 0; i < numOfEvents; ++i)
        printVEvent(events + i);
    printTail();
    //收尾阶段
    writeFile();
    closeScript();
    freeMem();
    return 0;
}
