#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tool.h"


typedef unsigned char uint8_t;


typedef struct cpu_t{
    unsigned int A : 24;
    unsigned int X : 24;
    unsigned int L : 24;
    unsigned int PC : 24;
    unsigned int SW : 24;
}cpu_t;

void show(void * memory, char * begin, char * end);

void load(char * target, void * memory, int * program_begin,  int * program_end, int * loaded);

void run(int * program_begin, int * program_end, void * memory, cpu_t * cpu);




