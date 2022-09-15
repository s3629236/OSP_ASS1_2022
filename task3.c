 #include "task3.h"
const int THREAD_COUNT = 13;
const int BUFFERCOUNT = 500;
    clock_t start3, end3;
    double cpu_time_used3;


struct args{
    char ** sortStringBuffer;
    int length;
    int fileNumber;
    char *filePath;
};

void map3(char *dirtyFile, char *cleanFile){

    char** validWords = taskOneFilter(dirtyFile, cleanFile);
    start3 = clock();
    //Final count of words in a buffer (words of 3 to 15 length)
    int wordCount[THREAD_COUNT]; 
    //Final count of all words from source file   
    int wordsInFileCount = lineCounter(cleanFile);

    //Sorted strings that have been split into their own buffer
    char **sortStringBuffer[THREAD_COUNT];
    //Used for naming the files
    int fileNumber = 3;
    //Paths of all files so we can pass them in with threads

    //Initialising all files and buffers
    for(int i = 0; i < THREAD_COUNT; i++){
        char sortedSubWordFileName[BUFFERCOUNT];

        snprintf(sortedSubWordFileName, BUFFERCOUNT, "./sortedmap3/%d.txt", i+3);

        if(mkfifo(sortedSubWordFileName, 0777) == -1){
            perror("Failed to create fifo, file already exists");
    }
        sortStringBuffer[i] = malloc(sizeof(char *) * wordsInFileCount);
        wordCount[i] = 0;
        fileNumber++;
    }

    //Switching based on the size of the word, placing into a buffer along with a related array for keeping count of how many words are in that buffer
    for(int i = 0; i < wordsInFileCount; i++){
        switch(strlen(validWords[i])-1){
            case 3:
                sortStringBuffer[0][wordCount[0]] = validWords[i];
                wordCount[0]++;
            break;
            case 4:
                sortStringBuffer[1][wordCount[1]] = validWords[i];
                wordCount[1]++;
            break;
            case 5:
                sortStringBuffer[2][wordCount[2]] = validWords[i];
                wordCount[2]++;
            break;
            case 6:
                sortStringBuffer[3][wordCount[3]] = validWords[i];
                wordCount[3]++;
            break;
            case 7:
                sortStringBuffer[4][wordCount[4]] = validWords[i];
                wordCount[4]++;
            break;
            case 8:
                sortStringBuffer[5][wordCount[5]] = validWords[i];
                wordCount[5]++;
            break;
            case 9:
                sortStringBuffer[6][wordCount[6]] = validWords[i];
                wordCount[6]++;
            break;
            case 10:
                sortStringBuffer[7][wordCount[7]] = validWords[i];
                wordCount[7]++;
            break;
            case 11:
                sortStringBuffer[8][wordCount[8]] = validWords[i];
                wordCount[8]++;
            break;
            case 12:
                sortStringBuffer[9][wordCount[9]] = validWords[i];
                wordCount[9]++;
            break;
            case 13:
                sortStringBuffer[10][wordCount[10]] = validWords[i];
                wordCount[10]++;
            break;
            case 14:
                sortStringBuffer[11][wordCount[11]] = validWords[i];
                wordCount[11]++;
            break;
            case 15:
                sortStringBuffer[12][wordCount[12]] = validWords[i];
                wordCount[12]++;
            break;
        }
    }


    //TODO: Create the timer here


    pthread_t mapThread[THREAD_COUNT]; 
    pthread_t reduceThread[THREAD_COUNT]; 
    //Create a global array
    for(int i = 0; i < THREAD_COUNT; i++){
        struct args *thread_args = (struct args *)malloc(sizeof(struct args));

        char *filePath = malloc(sizeof(char*) * 20);
        thread_args->sortStringBuffer = sortStringBuffer[i];
        thread_args->length = wordCount[i];
        //Magic number here as we are counting the offset only, this won't change
        thread_args->fileNumber = i+3;

    
        snprintf(filePath, BUFFERCOUNT, "./sortedmap3/%d.txt", i+3);
        thread_args->filePath = filePath;

        if(pthread_create(&reduceThread[i], NULL, &reduce3, (void *)thread_args)!=0){
            //Error occured
            printf("Error occured creating sort thread %d\n", i);
            exit(0);
        }

        if(pthread_create(&mapThread[i], NULL, &threaded_sort, (void *)thread_args)!=0){
            //Error occured
            printf("Error occured creating sort thread %d\n", i);
            exit(0);
        }
        //LAST null on join is the return value
        if(pthread_join(mapThread[i], NULL)!= 0){
            //Error occured
            printf("Error occured joining sort thread %d\n", i);
            exit(0);
        }
        if(pthread_join(reduceThread[i], NULL)!= 0){
            //Error occured
            printf("Error occured joining sort thread %d\n", i);
            exit(0);
        }
    }
    //TODO: End timer here
    end3 = clock();
    cpu_time_used3 = ((double) (end3 - start3)) / CLOCKS_PER_SEC;
    printf("Task 3 took: %f and cpu time used is %f\n",(double)(end3 - start3), cpu_time_used3);
}

//Pass the arguments in, set a temporary struct, sort that struct, write to a file
void *threaded_sort(void *threadarg){
    struct args *thread_args = (struct args *)threadarg;

    printf("Reached a thread\n");
    int fileDescriptor = open(thread_args->filePath, O_WRONLY);
    if(fileDescriptor == -1){
        printf("Failed to open fifo file: %d\n", thread_args->fileNumber);
    }
    printf("Managed to open file\n");
    qsort((*thread_args).sortStringBuffer, (*thread_args).length, sizeof(char*), compareString);
    for(int i = 0; i < thread_args->length; i++){
        if( write(fileDescriptor, thread_args->sortStringBuffer[i], sizeof(char*) * thread_args->fileNumber) == -1){
            printf("Failed to write to file %d: %s", thread_args->fileNumber, thread_args->sortStringBuffer[i]);
        }
    }
    close(fileDescriptor);
    return ((void*)thread_args);
}

void *reduce3(void *threadarg){
    struct args *thread_args = (struct args *)threadarg;
    //We need a filePath to open as write
    //We need a length to know the size of the file
    //
    printf("Hit reduce thread\n");
    return ((void*)thread_args);
}


//strerror
// use perror to print a system error message