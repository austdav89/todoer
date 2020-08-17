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
    printf("Available commands:\n\nadd <Todo Name>\nshow\nquit\n\n"); 
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

Todo * createTodo(void){
    
    Todo *node = (Todo *) malloc(sizeof(Todo));
    node -> next = NULL;
    
    return node;
}

int todoCount(Todo * head){
    int cnt = 0;

    if (!head)
        return cnt;
     
    while (head != NULL){
        cnt++;
        head = head -> next;
    }
    return cnt;
}

// main program loop
int todoerLoop(void){
    char *prompt = "TODO>"; //Universal prompt prefix
    char *linebuff = (char *)malloc(sizeof(char) * LINE_MAX);
    char *cmd, *arg;
    Todo *head, *tail, *trav;
    head = trav = NULL;

    while(true){
        trav = NULL;
        printf("%s", prompt);
        getInput(linebuff);
        
        if (!linebuff[0])
            continue;

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
               arg = NULL;
               break;
           }
        }
        // lookup for commands
        if (strcmp(cmd, "quit") == 0){
            printf("Good Bye!\n");
            return 0;
        }
        else if (strcmp(cmd, "add") == 0){
            if (arg){
                if (head){
                    tail -> next = createTodo();
                    tail = tail -> next;
                }
                else
                    head = tail = createTodo();
                
                tail -> name = malloc(sizeof(char) * strlen(arg + 1));
                strcpy(tail -> name, arg);
                }     
            else{
                printf("-add error: Todo name not supplied.\n");
            }
        }        
        else if (strcmp(cmd, "show") == 0){
            trav = head;

            for(int i = 0; i < todoCount(head); i++){
                printf("%i\t%s\n", i + 1, trav -> name);
                trav = trav -> next;
            }
        }
               
        else if (strcmp(cmd, "help") == 0){
            helpMsg();
        }
        else {
            printf("-TODO: %s: command not found\n", cmd);
        }
        cmd = arg = NULL;
    }
    // clean up
    if (linebuff)
        free(linebuff);
}
