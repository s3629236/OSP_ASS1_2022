#include "task2.h"

const int AMOUNT_OF_FORKS = 13;
const int BUFFERSIZE = 500;
int lineCounts[20];
const int AMOUNT_OF_FILES = 13;
/*Task 2: Process based Solution


Use reduce() to open each of the 13 files reading one line at a time for each file, and writing the lowest sort order
word from each file, and then reading the next word from that file. In other words, a 13 → 1 merge sort.*/


int compareStringByThirdCharacter( const void *str1, const void *str2 )
{
    char *const *pp1 = str1;
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
}



void map2(){

    char** validWords = taskOneFilter("tester.txt", "CTask1.txt");
    FILE *writeFile[AMOUNT_OF_FILES];
    FILE *sortedSubWordFile[AMOUNT_OF_FILES];
    int wordCount[AMOUNT_OF_FILES];
    

    //separate the words list into separate lists, one with words of length 3, the next of length 4, to 15.
    int wordsInFileCount = lineCounter("./CTask1.txt");

    char **sortStringBuffer[AMOUNT_OF_FILES];
    int fileNumber = 3;

    //Initialising all files and buffers
    for(int i = 0; i < AMOUNT_OF_FILES; i++){
        char subWordFileName[BUFFERSIZE];
        char sortedSubWordFileName[BUFFERSIZE];
        //Set filenames to be based on the amount of letters in the word
        snprintf(subWordFileName, BUFFERSIZE, "./map2/%d.txt", fileNumber);
        snprintf(sortedSubWordFileName, BUFFERSIZE, "./sortedmap2/%d.txt", fileNumber);
        writeFile[i] = fopen(subWordFileName, "w");
        sortedSubWordFile[i] = fopen(sortedSubWordFileName, "a");
        sortStringBuffer[i] = malloc(sizeof(char *) * wordsInFileCount);
        wordCount[i] = 0;
        fileNumber++;
    }

    for(int i = 0; i < wordsInFileCount; i++){
        switch(strlen(validWords[i])-1){
            case 3:
                int result = fprintf(writeFile[0], "%s", validWords[i]);
                printf("Threefile result is %d\n:", result);
                sortStringBuffer[0][wordCount[0]] = validWords[i];
                wordCount[0]++;
            break;
            case 4:
                fprintf(writeFile[1], "%s", validWords[i]);
                sortStringBuffer[1][wordCount[1]] = validWords[i];
                wordCount[1]++;
            break;
            case 5:
                fprintf(writeFile[2], "%s", validWords[i]);
                sortStringBuffer[2][wordCount[2]] = validWords[i];
                wordCount[2]++;
            break;
            case 6:
                fprintf(writeFile[3], "%s", validWords[i]);
                sortStringBuffer[3][wordCount[3]] = validWords[i];
                wordCount[3]++;
            break;
            case 7:
                fprintf(writeFile[4], "%s", validWords[i]);
                sortStringBuffer[4][wordCount[4]] = validWords[i];
                wordCount[4]++;
            break;
            case 8:
                fprintf(writeFile[5], "%s", validWords[i]); 
                sortStringBuffer[5][wordCount[5]] = validWords[i];
                wordCount[5]++;
            break;
            case 9:
                fprintf(writeFile[6], "%s", validWords[i]);
                sortStringBuffer[6][wordCount[6]] = validWords[i];
                wordCount[6]++;
            break;
            case 10:
                fprintf(writeFile[7], "%s", validWords[i]);
                sortStringBuffer[7][wordCount[7]] = validWords[i];
                wordCount[7]++;
            break;
            case 11:
                fprintf(writeFile[8], "%s", validWords[i]);
                sortStringBuffer[8][wordCount[8]] = validWords[i];
                wordCount[8]++;
            break;
            case 12:
                fprintf(writeFile[9], "%s", validWords[i]);
                sortStringBuffer[9][wordCount[9]] = validWords[i];
                wordCount[9]++;
            break;
            case 13:
                fprintf(writeFile[10], "%s", validWords[i]);
                sortStringBuffer[10][wordCount[10]] = validWords[i];
                wordCount[10]++;
            break;
            case 14:
                fprintf(writeFile[11], "%s", validWords[i]);
                sortStringBuffer[11][wordCount[11]] = validWords[i];
                wordCount[11]++;
            break;
            case 15:
                fprintf(writeFile[12], "%s", validWords[i]);
                sortStringBuffer[12][wordCount[12]] = validWords[i];
                wordCount[12]++;
            break;
        }
    }


 //closing all files 
    for(int i = 0; i < AMOUNT_OF_FILES; i++){
        fclose(writeFile[i]);
    }

    // pid_t pid = getpid();
    for(int i = 0; i <= AMOUNT_OF_FORKS; i++){
        //We are the child process
        // if(pid == 0){
            //Adding +2 here to account for the word lengths, sort(3) will access file "./map2/3.txt"
            sort(sortedSubWordFile[i], sortStringBuffer[i],wordCount[i], i+3);
        // }else{
        //     //We should be the parent process, make another fork!
        //     //printf("Creating a fork!\n");
        //     pid = fork();
        //     wait(0);
        // }
    }


    //closing all files 
    for(int i = 0; i < AMOUNT_OF_FILES; i++){
        fclose(sortedSubWordFile[i]);
    }


    //Don't allow the main process to continue until we have no child processes running
    while (wait(NULL) != -1 || errno != ECHILD); 



}

//Go through each file, grab the current index of that file and move to the merged array
//Need to find the length of all the files
void reduce(){

}

//Sorting all these files from a single thread
void singleThread(){

}

void sort(FILE *sortedSubWordFile, char** buffer, int sizeOfArray, int fileNumber){
    //Apply q sort to array being passed in
    qsort(buffer, sizeOfArray, sizeof(char*), compareString);
    //Fput the file 
        for(int i = 0; i < sizeOfArray; i++){
        printf("Printing to %d: %s", fileNumber, buffer[i]);
        printf("FILE: %p\n", sortedSubWordFile);
        int result = fputs(buffer[i], sortedSubWordFile);
        printf("FileNumber %d result is %d\n:", fileNumber, result);
    }

}

//Only run printf statements if passing the -DVERBOSE flag when compiling
#ifdef VERBOSE
#endif