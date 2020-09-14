
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "todoer.h"
#include "data.h"

char filePath[] = "~/";
char fileName[] = ".todoer";

int loadData(Todo **headptr){
    FILE *fptr;
    char fullPath[MAX_PATH_SIZE];
    char buff[LINE_MAX];
    char c;
    int  n;
    Todo *head = *headptr;
    Todo *trav = head;

    strcpy(fullPath, filePath);
    strcat(fullPath, fileName);

    if (fptr = fopen(fullPath, "r")){
        head = createTodo(); 
        while ((c = getc(fptr)) != EOF){
            n = 0;
            while (c != '\n'){
                
            }
        }
        return 1;
    } else 
        return 0;
}

int saveData(Todo *data, int num){
    FILE *fptr;
    char fullPath[MAX_PATH_SIZE];

    strcpy(fullPath, filePath);
    strcat(fullPath, fileName);
    //printf("Saving Data to %s...\n", fullPath);
    
    if (num){
        fptr = fopen("./.todoer", "w"); 
        if (fptr != NULL){
            for (int i = 0; i < num; i++){
                fwrite(data->name, sizeof(data->name), 1, fptr);
                fwrite("\n", 1, 1, fptr);
                fwrite(data->done ? "1":"0", 1, 1, fptr);
                fwrite("\n\n", 2, 1, fptr);
                data = data->next;
            }
            fclose(fptr);
        }
    }


    return true;
}
