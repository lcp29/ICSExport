
/*
 * boot.c
 * 开始阶段函数
 */

#include "defs.h"

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
        argFlag |= ONE_FILENAME;
        ++counter;
    }
    else if (counter == 1) //第二次执行
    {
        strncpy(outfileName, arg, NAME_MAX);
        argFlag &= ~ONE_FILENAME;
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
