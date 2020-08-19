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
    printf("Available commands:\n\nadd\t<Todo Name>\ndel\t<todo Num> (Use show cmd) \
    \ndone\t<todo Num> (Use show cmd)\nshow\nquit\n\n"); 
}

bool isNum(char *str){
    if (!str){
        return false;
    }

    while (*str != '\0'){
        if(*str < '0' || *str > '9')
            return false;
        str++;
    }

    return true;
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

int todoCount(Todo * head){
    int cnt = 0;

    if (!head)
        return cnt;
     
    while (head != NULL){
        cnt++;
        head = head->next;
    }

    return cnt;
}

Todo * createTodo(void){
    Todo *node = (Todo *) malloc(sizeof(Todo));
    node->next = NULL;
    node->done = false;

    return node;
}

void delTodo(Todo **headptr, int todoLen, int delNum){
    //temp is used for holding the delete bound address
    //and will be free at the end if used
    Todo *trav, *prev, *temp = NULL;
    trav = *headptr;
    
    if (todoLen < delNum || !delNum){
        printf("-del error: number out of scope\n");
    }
    else if (*headptr){
        if (delNum == 1){
            if (todoLen > 1){
                temp = *headptr;
                *headptr = (*headptr)->next;
            }
            else
                *headptr = NULL;
            }
        else {
            prev = *headptr;
            trav = prev->next;

            for(int i = 1; i < delNum - 1; i++){
                prev = trav;
                trav = prev->next;
            }
            temp = trav;
            prev->next = trav->next;
            trav = trav->next;
        }
    }
    if (temp){
        free(temp);
    }
}

// main program loop
int todoerLoop(void){
    char *prompt = "TODO>"; //Universal prompt prefix
    char *linebuff = (char *)malloc(sizeof(char) * LINE_MAX);
    char *cmd, *arg;
    Todo *head, *tail, *trav, **headptr;
    head = trav = NULL;
    headptr = &head;

    while(true){
        cmd = arg = NULL;
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
                    tail->next = createTodo();
                    tail = tail->next;
                }
                else
                    head = tail = createTodo();
                
                tail->name = malloc(sizeof(char) * strlen(arg + 1));
                strcpy(tail->name, arg);
                }     
            else{
                printf("-add error: Todo name not supplied\n");
            }
        }        
        else if (strcmp(cmd, "show") == 0){
            trav = head;
            
            if (head){
                printf("\tTodo#\tDone\tName\n");
                printf("\t--------------------------------\n");
                for(int i = 0; i < todoCount(head); i++){
                    if(trav->done == false)
                        printf("\t%i\t%s\t%s\n", i + 1,trav->done?"Yes":"No", trav->name);
                    trav = trav->next;
                }
                trav = head;
                for(int i = 0; i < todoCount(head); i++){
                    if(trav->done == true)
                        printf("\t%i\t%s\t%s\n", i + 1,trav->done?"Yes":"No", trav->name);
                    trav = trav->next;
                }

            }
        }
        else if (strcmp(cmd, "del") == 0){
            if (isNum(arg)){
                delTodo(headptr, todoCount(head), atoi(arg));
            }
        }
        else if (strcmp(cmd, "done") == 0){
            trav = head;
            if (isNum(arg)){
                for(int i = 1; i < atoi(arg); i++){
                    trav = trav->next;
                }
                trav->done = true;
            }
        }
        else if (strcmp(cmd, "help") == 0){
            helpMsg();
        }
        else {
            printf("-TODO: %s: command not found\n", cmd);
        }
    }
    // clean up
    if (linebuff)
        free(linebuff);
}
