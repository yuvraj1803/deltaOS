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

void sse_handler(){

   if(get_current_el() == 2){
        printf("sse not supported. OS not running under hypervisor.\n");
        return;
    }

    printf("Choose SSE operation:\n");
    printf("1. sse_fopen\n");
    printf("2. sse_fread\n");
    printf("3. sse_fwrite\n");
    printf("4. sse_fseek\n");
    printf("5. sse_rewind\n");
    printf("6. sse_fclose\n");
    printf("\n");

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

    printf("sse_fopen selected.\n");

    printf("File Path: ");
    char path[256];
    gets(path);

    printf("Mode (R/W): ");
    char* mode;
    gets(mode);

    int hv_response = sse_fopen((const char*) path, (const char*)&mode);

    if(hv_response >= 0) printf("%s opened.\n", path);
    else printf("File couldn't be opened.\n");

}
void sse_fread_handler(){

    printf("sse_fread selected.\n");

    printf("Enter file descriptor: ");
    char fdstr[10];
    gets(fdstr);
    int fd = stoi(fdstr);

    printf("Enter number of bytes to read: ");
    char bytesstr[10];
    gets(bytesstr);
    int bytes = stoi(bytesstr);

    char buffer[1024];

    int hv_response = sse_fread(buffer, bytes, 1, fd);

    if(hv_response >= 0){
        printf("%s\n", buffer);
    }else{
        printf("Couldn't read file.\n");
    }

}
void sse_fwrite_handler(){

    printf("sse_fwrite selected.\n");

    printf("Enter file descriptor: ");
    char fdstr[10];
    gets(fdstr);
    int fd = stoi(fdstr);

    printf("Enter data to write: ");
    char buffer[1024];
    gets(buffer);

    int bytes_entered = strlen(buffer);

    int hv_response = sse_fwrite(buffer, bytes_entered, 1, fd);

    if(hv_response >= 0){
        printf("Data written.\n");
    }else{
        printf("Couldn't write to the file.\n");
    }

}
void sse_fseek_handler(){

    printf("sse_fseek selected.\n");

    printf("Enter file descriptor: ");
    char fdstr[10];
    gets(fdstr);
    int fd = stoi(fdstr);

    printf("Enter offset: ");
    char offsetstr[10];
    gets(offsetstr);
    int offset = stoi(offsetstr);

    int hv_response = sse_fseek(fd, offset, 0);

    if(hv_response >= 0) printf("Pointer set to offset %d.\n", offset);
    else{
        printf("fseek failed.\n");
    }

}
void sse_rewind_handler(){

    printf("sse_rewind selected.\n");

    printf("Enter file descriptor: ");
    char fdstr[10];
    gets(fdstr);
    int fd = stoi(fdstr);

    int hv_response = sse_fseek(fd, 0,0);

    if(hv_response >= 0){
        printf("Rewind successful.\n");
    }else{
        printf("Rewind Failed.\n");
    }

}
void sse_fclose_handler(){

    printf("sse_fclose selected.\n");

    printf("Enter file descriptor: ");
    char fdstr[10];
    gets(fdstr);
    int fd = stoi(fdstr);

    int hv_response = sse_fclose(fd);

    if(hv_response >= 0){
        printf("File closed.\n");
    }else{
        printf("File couldn't be closed.\n");
    }

}