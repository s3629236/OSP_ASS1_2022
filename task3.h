#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "task1.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void map3(char *dirtyFile, char *cleanFile);

void *threaded_sort(void* threadarg);
void *reduce3(void *threadarg);