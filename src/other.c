
/*
 * other.c
 * 杂函数
 */

#include "defs.h"

void putUsage()
{
    printf("使用方法：icsexport.exe [参数] [脚本文件名] [iCalendar文件名]\n"
           "参数：\n"
           "  -h | --help    打印帮助文本，此时不会进行脚本转换\n\n"
           "注意：\n"
           "无参数时默认添加--help参数，没有--help参数时，多余的内容会被忽略。\n"
           "若未输入[iCalendar文件名]，则按照脚本文件名处理。");
}