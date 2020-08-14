#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "todoer.h"


// Welcome message
void welcomeMsg(void){
    printf("\nWelcome to ToDoer v%g!\n", VERSION);
    printf("Created by: Austin Davis\n");
    printf("Type \"help\" for a list of commands.\n\n");
}

void helpMsg(void){
    printf("\nToDoer is a checklist program to help prioritize the day.\n\n"); 
    printf("Available commands:\nhelp\nquit\n\n"); 
}

void getInput(char * str){
    char ch;
    int i = 0;

    if (str == NULL){
        fprintf(stderr, "Line buffer memory allocation failed\n");
        exit(-1);
    }

    while((ch = getchar()) != '\n'){
        str[i] = ch;
        i++;
    }
    str[i] = '\0';
}

// main program loop
int todoerLoop(void){
    char *prompt = "TODO>"; //Universal prompt prefix
    char *linebuff = (char *)malloc(sizeof(char) * LINE_MAX);
    char *cmd, *arg;

    while(true){
        printf("%s", prompt);
        getInput(linebuff);
        
        // parse linebuff to get command and args
        for (int i = 0; i < LINE_MAX; i++){
           if (linebuff[i] == ' '){
               linebuff[i] = '\0';
               cmd = linebuff;
               arg = &linebuff[i+1];
               break;
           }
            else if (linebuff[i] == '\0'){
               cmd = linebuff;
               break;
           }
        }
        // lookup for commands
        if (strcmp(cmd, "quit") == 0){
            printf("Good Bye!\n");
            return 0;
        }
        else if (strcmp(cmd, "help") == 0){
            helpMsg();
        }
        cmd = arg = NULL;
    }
    // clean up
    free(linebuff);
}
