
/*
 * defs.h
 * 存储常量，函数原型
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_MAX 255 //SM2.C.1

//SM2.F.1
#define PRINT_HELP 1              //SM2.C.2
#define ABORT 1 << 1              //SM2.C.3
#define UNDEFINED_ARG 1 << 2      //SM2.C.4
#define TOO_MANY_FILENAMES 1 << 3 //SM2.C.5

extern int argFlag; //SM2.F.1

extern char infileName[NAME_MAX];  //SM2.S.1
extern char outfileName[NAME_MAX]; //SM2.S.2
