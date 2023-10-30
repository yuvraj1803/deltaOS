#ifndef __KTHREAD_H__
#define __KTHREAD_H__

#include <stdint.h>
#include "mm/paging.h"

#define KTHREAD_RUNNING 0
#define KTHREAD_WAITING 1
#define KTHREAD_DEAD    2

struct kthread* kthread_init(char* name, void* kthread_function);
struct pt_regs* get_kthread_pt_regs(struct kthread* _kthread);
char* kthread_state_to_string(uint8_t state);

struct kthread_info{
    uint32_t prio;
    uint32_t quanta_remaining;
};

struct pt_regs{
	uint64_t regs[31];
	uint64_t sp;
	uint64_t pc;
	uint64_t pstate;
};

struct context{
    uint64_t x19;
    uint64_t x20;
    uint64_t x21;
    uint64_t x22;
    uint64_t x23;
    uint64_t x24;
    uint64_t x25;
    uint64_t x26;
    uint64_t x27;
    uint64_t x28;
    uint64_t fp;
    uint64_t sp; 
    uint64_t pc;
};

struct kthread{
    char name[256];
    uint8_t state;
    uint8_t pid;

    struct kthread_info info;
    struct virtual_address_space*   vaddr_space;
    
    void (*kthread_function)();

    struct context context;

};

#endif