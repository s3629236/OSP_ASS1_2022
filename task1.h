#ifndef TASK1_H
#define TASK1_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>  
#include<time.h>
#include<ctype.h>
#include <regex.h>

char** taskOneFilter(char* readFileLocation, char* cleanFileLocation);

int lineCounter();
int compareString( const void *str1, const void *str2 );
void printContents(char** array, int size);


#endif