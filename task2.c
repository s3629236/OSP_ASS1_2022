#include "task2.h"

const int AMOUNT_OF_FORKS = 13;
const int BUFFERSIZE = 500;
int lineCounts[20];
const int AMOUNT_OF_FILES = 13;
const int characterToBeSortedOn = 0;


void map2(){

    char** validWords = taskOneFilter("tester.txt", "CTask1.txt");
    FILE *sortedSubWordFile[AMOUNT_OF_FILES];
    int wordCount[AMOUNT_OF_FILES];
    

    //separate the words list into separate lists, one with words of length 3, the next of length 4, to 15.
    int wordsInFileCount = lineCounter("./CTask1.txt");

    char **sortStringBuffer[AMOUNT_OF_FILES];
    int fileNumber = 3;

    //Initialising all files and buffers
    for(int i = 0; i < AMOUNT_OF_FILES; i++){
        char sortedSubWordFileName[BUFFERSIZE];
        //Set filenames to be based on the amount of letters in the word
        snprintf(sortedSubWordFileName, BUFFERSIZE, "./sortedmap2/%d.txt", fileNumber);
        sortedSubWordFile[i] = fopen(sortedSubWordFileName, "w");
        if (sortedSubWordFile[i]== NULL) {
            perror("Failed to create a sub word file in task 2\n");
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

    //TODO: Create timer here
    pid_t pid = getpid();
    for(int i = 0; i < AMOUNT_OF_FORKS; i++){
        //If we are the child process
        if((pid = fork()) == 0){
            //Apply q sort to array being passed in
            qsort(sortStringBuffer[i], wordCount[i], sizeof(char*), compareString);
            //Fput the file 
            for(int j = 0; j < wordCount[i]; j++){
                fputs(sortStringBuffer[i][j], sortedSubWordFile[i]);
            }  
            exit(0);  
        }
    }
    //TODO: End timer here

    //closing all files 
    for(int i = 0; i < AMOUNT_OF_FILES; i++){
        fclose(sortedSubWordFile[i]);
    }

    //Don't allow the main process to continue until we have no child processes running
    while (wait(NULL) != -1 || errno != ECHILD){
        //printf("Waiting for children to finish\n");
    } 

  reduce(wordCount, wordsInFileCount);
}

//Go through each file, grab the current index of that file and move to the merged array
//Need to find the length of all the files

void reduce(int wordCount[], int totalLineCount){ 
    //Create a final file
    FILE *reducedFile;
    FILE *sortedSubWordFile[AMOUNT_OF_FILES];
    int positionInFile[AMOUNT_OF_FILES];

    char *mergeStrings[AMOUNT_OF_FILES];

    //Init file
    reducedFile = fopen("./sortedmap2/Task2Final.txt", "w");
    if (reducedFile == NULL) {
        perror("Failed to create the final reduced text file for task 2\n");
        exit(0);
    }

    //Open all files again
    for(int i = 0; i < AMOUNT_OF_FILES; i++){
        char sortedSubWordFileName[BUFFERSIZE];
        snprintf(sortedSubWordFileName, BUFFERSIZE, "./sortedmap2/%d.txt", i+3);
        sortedSubWordFile[i] = fopen(sortedSubWordFileName, "r");
        if (sortedSubWordFile[i] == NULL) {
            perror("Failed to read a subword file while reducing\n");
            exit(0);
        }
    }   

 
    int ignoreFile[AMOUNT_OF_FILES];
        for(int j = 0; j< AMOUNT_OF_FILES; j++){
            mergeStrings[j] = malloc(sizeof(char*) * (j+3));
            fgets(mergeStrings[j],sizeof(char*) * (j+3),sortedSubWordFile[j]);
            positionInFile[j] = 0;
            ignoreFile[j] = 0;
        }    


int finishedFileCount = 0;


    while(finishedFileCount < 13){
        char min = '~';
        int index = 0;
        //Iterate through every file, if this is the min word, then use this one
        for(int j = 0; j< AMOUNT_OF_FILES; j++){
            if((mergeStrings[j][characterToBeSortedOn] < min) && (ignoreFile[j] == 0)){
                //printf("The third character of %s is %d, which should be lower than %d\n", mergeStrings[j], mergeStrings[j][2], min);
                min = mergeStrings[j][characterToBeSortedOn];
                index = j;
            }                
        }    
        //Add the lowest alphabetical string to reduce file
        
        if(positionInFile[index] < wordCount[index]){
            //printf("Putting into file: %s", mergeStrings[index]);
            fputs(mergeStrings[index], reducedFile);
        }

        if(positionInFile[index] < wordCount[index]){
            fgets(mergeStrings[index],sizeof(char*) * (index+3),sortedSubWordFile[index]);
            positionInFile[index]++;
        }
        else{
            ignoreFile[index] = 1;
            finishedFileCount++;
        }

    }

    fclose(reducedFile);
}



//Only run printf statements if passing the -DVERBOSE flag when compiling
#ifdef VERBOSE
#endif 