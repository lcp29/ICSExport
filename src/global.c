
/*
 * global.h
 * 存放全局变量
 */

#include "defs.h"

int argFlag = 0; //SM2.F.1

char infileName[NAME_MAX];  //SM2.S.1
char outfileName[NAME_MAX]; //SM2.S.2

char firstMonday[9];        //SM2.S.3

FILE *src;    //SM2.P.1
FILE *dest;   //SM2.P.2
