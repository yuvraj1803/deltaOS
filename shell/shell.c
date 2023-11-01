#include "shell/shell.h"
#include "stdio.h"
#include "string.h"
#include <stdint.h>
#include "memory.h"
#include "mm/mm.h"  
#include "config.h"


struct shell* current_shell;
int total_shell_commands;

// ======================================================= Shell Command Handler Prototypes ========================================================================== //

void sse();

// =================================================================================================================================================================== //


int8_t add_shell_command(char name[], void* command_handler){
    if(total_shell_commands == CONFIF_MAX_SHELL_CMDS){
        printf("Max shell commands limit reached. Couldn't add command: %s\n", name);
        return -1;
    }

    current_shell->commands[total_shell_commands] = (struct shell_command*) malloc(sizeof(struct shell_command));
    strcpy(current_shell->commands[total_shell_commands]->name, name);
    current_shell->commands[total_shell_commands]->command_handler = command_handler;
    

    total_shell_commands++;
    return 0;
}

void shell_init(){

    current_shell = (struct shell*) malloc(sizeof(struct shell));

    total_shell_commands = 0;
    add_shell_command("sse", &sse);


    log("Shell initialised.");
}

void shell_run(){

    printf(">>> ");
    char input[256];    // i am not checking for buffer overflow here since its a test environment. 
    gets(input);

    for(int command=0 ; command < total_shell_commands ; command++){
        if(current_shell->commands[command] != 0 && !strcmp(current_shell->commands[command]->name, input)){
            current_shell->commands[command]->command_handler();
        }
    }

    printf("command not found.\n");
}

// ======================================================= Shell Command Handlers ========================================================================== //

#define SSE_OPERATION_FOPEN         1
#define SSE_OPERATION_FREAD         2
#define SSE_OPERATION_FWRITE        3
#define SSE_OPERATION_FSEEK         4
#define SSE_OPERATION_REWIND        5
#define SSE_OPERATION_FCLOSE        6

void sse_fopen_handler();
void sse_fread_handler();
void sse_fwrite_handler();
void sse_fseek_handler();
void sse_rewind_handler();
void sse_fclose_handler();

void sse(){
    printf("Choose SSE operation:\n");
    printf("1. sse_fopen\n");
    printf("2. sse_fread\n");
    printf("3. sse_fwrite\n");
    printf("4. sse_fseek\n");
    printf("5. sse_rewind\n");
    printf("6. sse_fclose\n");

    int op = getch() - '0';

    if(op >= 1 && op <= 6){
        switch (op){
            case 1:
                sse_fopen_handler();
                break;
            case 2:
                sse_fread_handler();
                break;
            case 3:
                sse_fwrite_handler();
                break;
            case 4:
                sse_fseek_handler();
                break;
            case 5:
                sse_rewind_handler();
                break;
            case 6:
                sse_fclose_handler();
                break;    
        }
    }else{
        printf("Invalid SSE operation.\n");
        return;       
    }

}

void sse_fopen_handler(){

}
void sse_fread_handler(){

}
void sse_fwrite_handler(){

}
void sse_fseek_handler(){

}
void sse_rewind_handler(){

}
void sse_fclose_handler(){

}