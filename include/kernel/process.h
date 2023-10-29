#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <stdint.h>

#define PROCESS_RUNNING 0
#define PROCESS_WAITING 1
#define PROCESS_DEAD    2

#define PROCESS_LOAD_ADDRESS    0x100000
#define PROCESS_STACK_BASE      0x100000-1

struct process* process_init(char* name, void* process_function);
void prepare_process();
struct pt_regs* get_process_pt_regs(struct process* _process);
char* process_state_to_string(uint8_t state);

struct process_info{
    uint32_t prio;
    uint32_t quanta_remaining;
};

struct pt_regs{
	uint64_t regs[31];
	uint64_t sp;
	uint64_t pc;
	uint64_t pstate;
};

struct process{
    char name[256];
    uint8_t state;
    uint8_t pid;

    struct process_info info;

    void (*process_function)();

};

#endif