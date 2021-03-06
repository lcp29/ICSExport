
/*
 * fop.c
 * 文件相关操作
 */

#include "defs.h"

FILE *src = NULL;  //SM2.P.1
FILE *dest = NULL; //SM2.P.2

void openScript()
{
    src = fopen(infileName, "r");
    if (src == NULL)
    {
        fileFlag |= ABORT;
        fileFlag |= OPEN_ERROR;
        return;
    }
    if (argFlag & ONE_FILENAME)
    {
        int i;
        for (i = strlen(infileName) - 1; i > 0 && infileName[i] != '.'; --i)
            ;
        if (i == 0)
            i = strlen(infileName) - 1;
        strncpy(outfileName, infileName, i);
        strcat(outfileName, ".ics");
    }
    dest = fopen(outfileName, "w+");
    return;
}

void fileFlagDealer()
{
    if (fileFlag & OPEN_ERROR)
    {
        printf("错误：文件打开失败。");
        return;
    }
}

void closeScript()
{
    fclose(src);
    fclose(dest);
    return;
}

void readLine()
{
    fgets(lbuf, LINE_MAX, src);
    if (feof(src))
        fileFlag |= SEOF;
    return;
}

/* readNextUnemptyLine()的正确用法
    while(1)
    {
        readNextUnemptyLine();
        if(fileFlag & SEOF)
            break;
        printf("%s", lbuf);
    }
*/

void readNextUnemptyLine()
{
    int isEmpty = 1;
    while (isEmpty && !(fileFlag & SEOF))
    {
        readLine();
        for (int i = 0; lbuf[i] != '\0'; ++i)
            if (lbuf[i] != ' ' && lbuf[i] != '\n' && lbuf[i] != '\t')
            {
                isEmpty = 0;
                break;
            }
    }
    return;
}

void readNextUnannoedUnemptyLine()
{
    int isAnnoed = 1;
    int i = 0;
    while (isAnnoed && !(fileFlag & SEOF))
    {
        readNextUnemptyLine();
        if(lbuf[i] != '#') //以#开头是注释
            isAnnoed = 0;
    }
    return;
}

void writeFile()
{
    fprintf(dest, "%s", obuf);
    return;
}
