/*
 * icsexport.c
 * .ics课表导出工具
 * 
 * 一些解释需要参阅./doc/软件维护手册.md
 * 引用格式：SM<对应章节>
 * 
 */

#include "defs.h"

void readArguments(int argc, const char *argv[]); //SM1.B.1
void putUsage();                                  //SM1.O.1
void argumentTranslator(const char *arg);         //SM1.B.2
void filenameReader(const char *arg);             //SM1.B.3
void argFlagDealer();                             //SM1.B.4

int main(int argc, char *argv[])
{
    //开始阶段
    readArguments(argc, argv);
    argFlagDealer();
    if (argFlag & ABORT)
        return 0;
    //读取文件

    return 0;
}

void readArguments(int argc, const char *argv[])
{
    if (argc == 1)
    {
        argFlag |= PRINT_HELP;
        return;
    }
    else
    {
        for (int i = 1; i <= argc - 1; ++i)
        {
            if (argv[i][0] == '-')
                argumentTranslator(argv[i]);
            else
                filenameReader(argv[i]);
        }
        return;
    }
}

void putUsage()
{
    printf("使用方法：icsexport.exe [参数] [脚本文件名] [iCalendar文件名]\n"
           "参数：\n"
           "  -h | --help    打印帮助文本，此时不会进行脚本转换\n\n"
           "注意：\n"
           "无参数时默认添加--help参数，没有--help参数时，多余的内容会被忽略。\n"
           "若未输入[iCalendar文件名]，则按照脚本文件名处理。");
}

void argumentTranslator(const char *arg)
{
    if (!strcmp(arg, "-h") || !strcmp(arg, "--help"))
    {
        argFlag |= PRINT_HELP;
        argFlag |= ABORT;
    }
    else
    {
        argFlag |= UNDEFINED_ARG;
        argFlag |= ABORT;
    }
    return;
}

void filenameReader(const char *arg)
{
    static int counter = 0; //存储当前的读取状态
    if (counter == 0)       //第一次执行
    {
        strncpy(infileName, arg, NAME_MAX);
        ++counter;
    }
    else if (counter == 1) //第二次执行
    {
        strncpy(outfileName, arg, NAME_MAX);
        ++counter;
    }
    else
    {
        argFlag |= TOO_MANY_FILENAMES;
    }
    return;
}

void argFlagDealer()
{
    if (argFlag & UNDEFINED_ARG)
        printf("错误：存在未知参数，请检查参数列表。\n\n");
    if (argFlag & TOO_MANY_FILENAMES)
        printf("警告：检测到有多于两个的文件名被传入，多余的部分将被忽略。\n\n");
    if (argFlag & PRINT_HELP)
        putUsage();
    return;
}
