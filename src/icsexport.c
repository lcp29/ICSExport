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
    /*
    int a;
    Token *t = genToken("1-2,3-4", &a);
    printf("%d\n\n", a);
    for (int i = 0; i < a; ++i)
        printf("%-12d%-12d%-12d%-12d\n", t[i].type, t[i].b, t[i].be[0], t[i].be[1]);*/
    return 0;
}
