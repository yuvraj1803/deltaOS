#include "shell/shell.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include "memory.h"


struct shell current_shell;
int total_shell_commands;


int8_t add_shell_command(char* name, void* command_handler){
    if(total_shell_commands == CONFIF_MAX_SHELL_CMDS){
        printf("Max shell commands limit reached. Couldn't add command: %s\n", name);
        return -1;
    }

    current_shell.commands[total_shell_commands++] = command_handler;
    return 0;
}

void shell_init(){
    memset(&current_shell, 0, sizeof(current_shell));
    total_shell_commands = 0;



}

void shell_run(){

    printf(">>> ");
    char input[256];    // i am not checking for buffer overflow here since its a test environment. 
    gets(input);

    for(int command=0 ; command < total_shell_commands ; command++){
        if(!strcmp(current_shell.commands[command]->name, input)){
            current_shell.commands[command]->command_handler();
        }
    }

    printf("command not found.\n");
}