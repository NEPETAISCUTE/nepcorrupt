#ifndef nepcorrupt
#define nepcorrupt

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <errno.h>

void printhelp();

int getStringHash(char*);

int doOp(int,char,uint8_t);

int editfile(char*,char*,char*,uint64_t,uint64_t,uint8_t,uint8_t);

char* dectohex(uint64_t);

uint64_t power(int,int);


uint64_t hextodec(char*);

#endif //nepcorrupt
