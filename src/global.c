
/*
 * global.h
 * 存放全局变量
 */

#include "defs.h"

int argFlag = 0;  //SM2.F.1
int fileFlag = 0; //SM2.F.2

char infileName[NAME_MAX];  //SM2.S.1
char outfileName[NAME_MAX]; //SM2.S.2

char firstMonday[9]; //SM2.S.3

char lbuf[LINE_MAX]; //SM2.S.4

struct CNUM *clses; //SM2.T.1

int numOfClasses = 1; //SM2.O.1
