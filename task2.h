#ifndef TASK2_H
#define TASK2_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>  
#include<time.h>
#include<ctype.h>
#include <regex.h>
#include "task1.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void map2();

void sort(FILE *sortedSubWordFile, char** buffer, int sizeOfArray, int fileNumber);

#endif