
/*
 * defs.h
 * 存储常量，函数原型
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define NAME_MAX 255 //SM2.C.1
#define LINE_MAX 255 //SM2.C.7

//SM2.F.1
#define PRINT_HELP 1              //SM2.C.2
#define ABORT 1 << 1              //SM2.C.3
#define UNDEFINED_ARG 1 << 2      //SM2.C.4
#define TOO_MANY_FILENAMES 1 << 3 //SM2.C.5
#define ONE_FILENAME 1 << 4       //SM2.C.6

//SM2.F.2
#define OPEN_ERROR 1 //SM2.C.8
//#define ABORT 1 << 1
#define SEOF 1 << 2 //SM2.C.13

#define UID_LENGTH 31  //SM2.C.9
#define LOC_MAX 31     //SM2.C.10
#define SUMMARY_MAX 15 //SM2.C.11
#define DES_MAX 63     //SM2.C.12

#define TIMEZONE 28800 //2.C.14

typedef struct VEVENT //SM3.1
{
    char DTSTAMP[17];
    char UID[UID_LENGTH + 1];
    char DTEND[16];
    char DTSTART[16];
    int isRec;
    int recCount;
    char LOCATION[LOC_MAX + 1];
    char DESCRIPTION[DES_MAX + 1];
}VEVENT;

typedef struct CNUM //SM3.2
{
    char CBEGIN[7];
    char CEND[7];
}CNUM;

extern int argFlag;  //SM2.F.1
extern int fileFlag; //SM2.F.2

extern char infileName[NAME_MAX];  //SM2.S.1
extern char outfileName[NAME_MAX]; //SM2.S.2

extern char firstMonday[9]; //SM2.S.3
extern char lbuf[LINE_MAX]; //SM2.S.4

extern CNUM *clses; //SM2.T.1

extern int numOfClasses; //SM2.O.1

//boot.c
void readArguments(int argc, const char *argv[]); //SM1.B.1
void argumentTranslator(const char *arg);         //SM1.B.2
void filenameReader(const char *arg);             //SM1.B.3
void argFlagDealer();                             //SM1.B.4

//other.c
void putUsage(); //SM1.O.1

//dateop.c
void evalFirstMonday(int weekcnt, const char *monOfThis); //SM1.D.1
void nextDay(const char *now, char *next);                //SM1.D.2
void lastDay(const char *now, char *last);                //SM1.D.3
int isLeapYear(int now);                                  //SM1.D.4
void nextWeek(const char *now, char *next);               //SM1.D.5
void lastWeek(const char *now, char *last);               //SM1.D.6

//fop.c
void openScript();                  //SM1.F.1
void fileFlagDealer();              //SM1.F.2
void closeScript();                 //SM1.F.3
void readLine();                    //SM1.F.4
void readNextUnemptyLine();         //SM1.F.5
void readNextUnannoedUnemptyLine(); //SM1.F.6

//proc.c
void readHead(); //SM1.P.1
void freeMem();  //SM1.P.2

//clk.c
void genGmStamp(char *stamp); //SM1.C.1
void genUID(char *uid);       //SM1.C.2
void randInit();              //SM1.C.3
