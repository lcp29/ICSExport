
/* analyzer.c
 * 日期/时间序列的语义分析
 */

#include "defs.h"

Token *genToken(const char *dbuf, int *n)
{
    int sz = 0; //Token数目
    for (int i = 0; i < strlen(dbuf); ++i)
        if (dbuf[i] == ',')
            ++sz;
    ++sz;
    *n = sz;
    Token *token = malloc(sizeof(Token) * sz);
    char abuf[7];       //存储数值，这里的大小就写死了o
    int c = 0;          //abuf索引
    int tokenIndex = 0; //token索引
    for (int i = 0; i <= strlen(dbuf); ++i)
    {
        if (dbuf[i] == '-')
        {
            abuf[c] = '\0';
            token[tokenIndex].type = 2;
            token[tokenIndex].be[0] = atoi(abuf);
            ++i;
            c = 0;
            for (; dbuf[i] != ',' && dbuf[i] != '\0'; ++i)
                abuf[c++] = dbuf[i];
            abuf[c] = '\0';
            token[tokenIndex].be[1] = atoi(abuf);
            ++tokenIndex;
        }
        if (dbuf[i] == ',' || dbuf[i] == '\0')
        {
            abuf[c] = '\0';
            token[tokenIndex].type = 1;
            token[tokenIndex].b = atoi(abuf);
            ++tokenIndex;
            ++i;
            c = 0;
        }
        abuf[c++] = dbuf[i];
    }
    return token;
}
