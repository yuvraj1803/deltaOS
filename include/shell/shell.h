#ifndef __SHELL_H__
#define __SHELL_H__

#include "config.h"

struct shell_command{
    char name[128];
    void (*command_handler)();
};

struct shell{
    struct shell_command* commands[CONFIG_MAX_SHELL_CMDS];
};

void shell_init();
void shell_run();



#endif