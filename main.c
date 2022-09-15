
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include <signal.h>

const int TIME_TO_EXIT = 25;

void sig_handler(int signum){
    printf("Reached alarm, exiting\n");
    exit(0);
}

//Each task should not last longer than 10 seconds
//ALL ACTIONS SHOULD BE PRINTED
int main(int argc, char* argv[]){
    signal(SIGALRM,sig_handler);
    //TODO for task 1, make sure it takes the filename as an input in the parameters for testers
    alarm(TIME_TO_EXIT);
    switch ((*argv)[1]){
        case 47:
        taskOneFilter(argv[2],argv[3]);
        break;
        case 48:
        map2(argv[2],argv[3]);
        break;
        case 49:
        map3(argv[2],argv[3]);
        break;
        case 50:
        //Unfinished
        print("Task 4 hasnt been implemented\n");
        break;
        case 51:
         print("Task 5 hasnt been implemented\n");
        //Unfinished
        break;
    }

    //map3("tester.txt","CTask1.txt");
    return 0;
}