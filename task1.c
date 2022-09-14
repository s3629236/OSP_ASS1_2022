#include "task1.h"

const int MIN_WORD_LENGTH = 3;
const int MAX_WORD_LENGTH = 15;
const int BUFFER_SIZE = 500;
const char *regexPattern = "[a-zA-Z&-]*";
int counter = 0;
int finalCounter = 0;

void printContents(char** array, int size){
    for (int i = 0; i < size; i++){
        printf("%s", array[i]);
    }
}

char* convertStringToLower(char inputString[]){
    int len = strlen(inputString);
    char *lowerCase = calloc(len+1, sizeof(char));
    for (int i = 0; i < len; ++i) {
        lowerCase[i] = tolower((unsigned char) inputString[i]);
    }
    return lowerCase;
}

bool acceptWord(const char *str, const char *pattern)
{
    regex_t regex;
    int result;

    //Compile regex
    regcomp(&regex, pattern, REG_EXTENDED);

    result = regexec(&regex, str, (size_t) 0, NULL, 0);
    regfree(&regex);

    if (result == 0){
        return true;
    }
    
    return false;
}

int compareString( const void *str1, const void *str2 )
{
    char *const *pp1 = str1;
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
}

char** taskOneFilter(char* readFileLocation, char* cleanFileLocation){
    //Open File
    FILE *readFilePtr;
    FILE *cleanFilePtr;
    //Allocating enough memory to accomodate the amount of unfiltered words
    char **cleanStringBuffer = malloc(sizeof(char *) * lineCounter(readFileLocation));
    //Final string buffer will contain the very final version of the word list
    char **finalStringBuffer = malloc(sizeof(char *) * lineCounter(readFileLocation));
    char wordBuffer[BUFFER_SIZE];
    readFilePtr = fopen(readFileLocation,"r");
    if (readFilePtr == NULL) {
        perror("Failed to open readfile");
        exit(0);
    }
    cleanFilePtr = fopen(cleanFileLocation, "w");
    if (cleanFilePtr == NULL) {
        perror("Failed to create or open cleanfile");
        exit(0);
    }

    //Going through all lines of the original file
    while (fgets(wordBuffer, sizeof(wordBuffer), readFilePtr)) {    
        //Get words that are <3 and >15
        if(strlen(wordBuffer) >= 4 && strlen(wordBuffer) <= 16){
            char* lowercaseString = convertStringToLower(wordBuffer);
            //Use the regex expression to deny anything outside of the intended pattern
            if(acceptWord(lowercaseString, regexPattern)){
                cleanStringBuffer[counter] = lowercaseString;
                counter++;
            }

        }
    }

    //Sort the array
    qsort(cleanStringBuffer, counter, sizeof(char*), compareString);

    //Removing duplicates from sorted array
    for(int i = 1; i < counter; i++){
        if(strcmp(cleanStringBuffer[i], cleanStringBuffer[i-1]) != 0){          
            finalStringBuffer[finalCounter] = cleanStringBuffer[i];            
            finalCounter = finalCounter+1;
        }
        else{
            printf("found a duplicate: %s\n", cleanStringBuffer[i]);
        }
    }

    //Push buffer to file
    for(int i = 0; i < finalCounter; i++){
        fputs(finalStringBuffer[i], cleanFilePtr);
    }
    fclose(readFilePtr);
    fclose(cleanFilePtr);
    return finalStringBuffer;
}


int lineCounter(char* fileLocation){
    FILE* readFilePtr = fopen(fileLocation, "r");
     if (readFilePtr == NULL) {
        perror("Failed to open readfile when counting lines");
        exit(0);
    }
    int numberOfLines = 0;
    char newLineCharacter;

    newLineCharacter = getc(readFilePtr);

    while (newLineCharacter != EOF)
    {
        //Count whenever new line is encountered
        if (newLineCharacter == '\n')
        {
            numberOfLines++;
        }
        //take next character from file.
        newLineCharacter = getc(readFilePtr);
    }
    fclose(readFilePtr);
    return numberOfLines;         

}


