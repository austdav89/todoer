/* This is the main file for ToDoer. All supporting functions and configs are in todoer.c and todoer.h */

#include <stdio.h>
#include <stdbool.h>

#include "todoer.h"

int main(void){
    
    welcomeMsg();
    todoerLoop();

    return 0;
}
