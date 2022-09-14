 #include "task3.h"
const int THREAD_COUNT = 13;
const int BUFFERCOUNT = 500;
// /*
// Task 3: Threads using FIFO files
// Here, we use FIFO files to transfer the data from map3() to threaded_sort(). Specifically

// •
// The main program calls the filter function to clean the data. The function will return a global string array of valid
// words. then main() creates both the map3() and threaded_sort() threads.

// The map3() function creates 13 index arrays and threads, one for each word length, indexing into the main string
// array. So if the global array contained [ “air”, ”airbag”, ”and” ] an index array had [1,3,…] then global[index[0]] is
// ‘air’, global[index[1]] = ‘and’.
// Global[] is only ever read by map before the threads, and only thread3 reads index3[]. Since no word can be two
// lengths at the same time, there will never be a conflict between threads .
// Having created the mapping, map3() now creates 13 threads. Each thread uses the C function qsort() to perform
// the same sort as before – on the third letter onwards – and when done, it creates 13 FIFO files opened for write
// and each thread will then output words to their corresponding file.
// In this case, the threaded_sort() function will wait, and then read those same 13 files, one line at a time in sort order.
// a. Note that an efficient way to sort is to swap indexes or pointers in the compare instead of swapping
// strings.
// This should produce the same file as Task2 (and Task 1 – after sorting ) (ignoring chars 1,2).
// This should produce the same file as Task2 (and Task 1 – after sorting. ) (ignoring chars 1,2).
// At the end, each thread opens a FIFO file for writing, and dumps the global strings in sorted index order.
// threaded_sort() should keep a count of words for each thread.
// Meanwhile, threaded_sort() needs only to perform the reduction merge step. It waits for each map3() thread to signal
// its completion. When all are done, threaded_sort() will open all 13 FIFO files for read, and perform the merge step as in
// Task2,
// a. Note that it may be necessary to set up all FIFO files before anything is read, as a FIFO open for read has to
// be created before an open for write. Thus this ‘wiring’ can be done in main() before the threads are
// created, and they inherit their files.
// At the end, task3 should output the word counts for each word length. Also present these as a percentage (for
// example 8% were words of length 10)

// Report: Compare performance. Consider where the time was saved or lost.*/


struct args{
    char ** sortStringBuffer;
    int length;
    int wordLength;
};

void map3(char *dirtyFile, char *cleanFile){



    char** validWords = taskOneFilter(dirtyFile, cleanFile);
    FILE *sortedSubWordFile[THREAD_COUNT];
    int wordCount[THREAD_COUNT];
    

    //separate the words list into separate lists, one with words of length 3, the next of length 4, to 15.
    int wordsInFileCount = lineCounter(cleanFile);

    char **sortStringBuffer[THREAD_COUNT];
    int fileNumber = 3;

    //Initialising all files and buffers
    for(int i = 0; i < THREAD_COUNT; i++){
        char sortedSubWordFileName[BUFFERCOUNT];
        //Set filenames to be based on the amount of letters in the word
        snprintf(sortedSubWordFileName, BUFFERCOUNT, "./sortedmap3/%d.txt", fileNumber);
        sortedSubWordFile[i] = fopen(sortedSubWordFileName, "w");
        if (sortedSubWordFile[i] == NULL) {
            perror("Failed to create a subword file before mapping in Task 3\n");
            exit(0);
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

    //closing all files 
    for(int i = 0; i < THREAD_COUNT; i++){
        fclose(sortedSubWordFile[i]);
    }
    //TODO: Create the timer here
    //0777 is full read and write permission
    //mkfifo(name, 0777);

    pthread_t thread[THREAD_COUNT]; 
    //Create a global array
    for(int i = 0; i < THREAD_COUNT; i++){
        struct args *thread_arguments = (struct args *)malloc(sizeof(struct args));
        struct args* return_args;
        thread_arguments->sortStringBuffer = sortStringBuffer[i];
        thread_arguments->length = wordCount[i];
        //Magic number here as we are counting the offset only, this won't change
        thread_arguments->wordLength = i+3;


        if(pthread_create(&thread[i], NULL, &threaded_sort, (void *)thread_arguments)!=0){
            //Error occured
            printf("Error occured creating a thread\n");
            exit(0);
        }
        //LAST null on join is the return value
        if(pthread_join(thread[i], (void**)&return_args)!= 0){
            //Error occured
            printf("Error occured joining thread %d\n", i);
            exit(0);
        }
    }

    //TODO: End timer here

}


//Pass the arguments in, set a temporary struct, sort that struct and then return
void *threaded_sort(void *threadarg){

    struct args *thread_arguments = (struct args *)threadarg;
    printf("Thread has word count of: %d\n", ((struct args*)threadarg)->length);
    qsort((*thread_arguments).sortStringBuffer, (*thread_arguments).length, sizeof(char*), compareString);
        for(int i = 0; i < thread_arguments->length; i++){
        fputs(thread_arguments->sortStringBuffer[i], cleanFilePtr);
    }
    return ((void*)thread_arguments);
}

void reduce3(){

}


//strerror
// use perror to print a system error message