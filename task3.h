#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "task1.h"


void map3(char *dirtyFile, char *cleanFile);

void *threaded_sort(void* threadarg);
void reduce3();