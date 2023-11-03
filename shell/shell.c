#include "shell/shell.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <stdint.h>
#include "memory.h"
#include "mm/mm.h"  
#include "config.h"
#include "sse.h"
#include "kernel/misc.h"


struct shell* current_shell;
int total_shell_commands;

// ======================================================= Shell Command Handler Prototypes ========================================================================== //

void sse_handler();

// =================================================================================================================================================================== //


int8_t add_shell_command(char name[], void* command_handler){
    if(total_shell_commands == CONFIG_MAX_SHELL_CMDS){
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
    add_shell_command("sse", &sse_handler);


    log("Shell initialised.");
}

void shell_run(){

 

    printf("deltaOS >>> ");
    char input[256];    // i am not checking for buffer overflow here since its a test environment. 
    gets(input);

    uint8_t command_found = 0;

    for(int command=0 ; command < total_shell_commands && !command_found; command++){
        if(current_shell->commands[command] != 0 && !strcmp(current_shell->commands[command]->name, input)){
            current_shell->commands[command]->command_handler();
            command_found = 1;
        }
    }

    if(!command_found) printf("command not found.\n");
}

// ======================================================= Shell Command Handlers ========================================================================== //

#define SSE_OPERATION_FREAD         1
#define SSE_OPERATION_FWRITE        2

void sse_fread_handler();
void sse_fwrite_handler();

void sse_handler(){
   if(get_current_el() == 2){
        printf("sse not supported. OS not running under hypervisor.\n");
        return;
    }
    printf("Choose SSE operation:\n");
    printf("1. sse_fread\n");
    printf("2. sse_fwrite\n");
    printf("\n");

    printf("--->");
    int op = getch() - '0';

    if(op >= 1 && op <= 2){
        switch (op){
            case 1:
                sse_fread_handler();
                break;
            case 2:
                sse_fwrite_handler();
                break;
        }
    }else{
        printf("Invalid SSE operation.\n");
        return;       
    }

}
void sse_fread_handler(){

    printf("sse_fread selected.\n");

    printf("Enter filename: ");
    char filename[128];
    gets(filename);

    printf("Enter number of bytes to read: ");
    char bytesstr[10];
    gets(bytesstr);
    int bytes = stoi(bytesstr);

    char buffer[1024];

    int hv_response = sse_fread(filename, buffer, bytes);

    if(hv_response >= 0){
        printf("%s\n", buffer);
    }else{
        printf("Couldn't read file.\n");
    }

}
void sse_fwrite_handler(){

    printf("sse_fwrite selected.\n");

    printf("Enter filename: ");
    char filename[128];
    gets(filename);

    printf("Enter data to write: ");
    char buffer[1024];
    gets(buffer);

    int bytes_entered = strlen(buffer);

    int hv_response = sse_fwrite(filename, buffer, bytes_entered);

    if(hv_response >= 0){
        printf("Data written.\n");
    }else{
        printf("Couldn't write to the file.\n");
    }

}
