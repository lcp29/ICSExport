
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
#define ONE_FILENAME 1 << 4       //SM2.C.6

extern int argFlag; //SM2.F.1

extern char infileName[NAME_MAX];  //SM2.S.1
extern char outfileName[NAME_MAX]; //SM2.S.2

extern char firstMonday[9];        //SM2.S.3

extern FILE *src;    //SM2.P.1
extern FILE *dest;   //SM2.P.2

//boot.c
void readArguments(int argc, const char *argv[]); //SM1.B.1
void argumentTranslator(const char *arg);         //SM1.B.2
void filenameReader(const char *arg);             //SM1.B.3
void argFlagDealer();                             //SM1.B.4

//other.c
void putUsage();                                  //SM1.O.1

//dateop.c
void evalFirstMonday(int weekcnt, const char* monOfThis); //SM1.D.1
void nextDay(const char* now, char *next);                //SM1.D.2
void lastDay(const char* now, char *last);                //SM1.D.3
int isLeapYear(int now);                                  //SM1.D.4
void nextWeek(const char* now, char *next);               //SM1.D.5
void lastWeek(const char* now, char *last);               //SM1.D.6
