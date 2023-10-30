#include "kernel/kthread.h"
#include "config.h"
#include "stdio.h"
#include "string.h"
#include "mm/mmu.h"
#include "mm/paging.h"
#include "mm/mm.h"

struct kthread* kthread_list[CONFIG_MAX_KTHREADS];
int total_kthreads = 0;

struct kthread* kthread_init(char* name, void* kthread_function){

    if(total_kthreads == CONFIG_MAX_KTHREADS){
		printf("[LOG]: Failed to load %s. Max kthread limit reached.", name);
        return 0;
    }
    
    struct kthread* _kthread = (struct kthread*) malloc(sizeof(struct kthread));
    if(!_kthread){
		printf("[LOG]: Failed to load %s.\n", name);
        return 0;
    }
    strcpy(_kthread->name, name);

    _kthread->info.quanta_remaining = CONFIG_SCHED_QUANTA;
    _kthread->info.prio = _kthread->info.quanta_remaining;

    _kthread->pid = total_kthreads;
    _kthread->state = KTHREAD_WAITING;

    _kthread->context.pc = (uint64_t) kthread_function;
    _kthread->context.sp = (uint64_t) get_kthread_pt_regs(_kthread);

    total_kthreads++;

    printf("LOG: [PID: %d] %s loaded.\n",_kthread->pid, _kthread->name);

    return _kthread;
}

struct pt_regs* get_kthread_pt_regs(struct kthread* _kthread){
    return (struct pt_regs*) ((uint64_t)_kthread + PAGE_SIZE - sizeof(struct pt_regs));
}
char* kthread_state_to_string(uint8_t state){
        switch(state){
            case 0:
                return "WAITING";
            case 1:
                return "RUNNING";
            case 2:
                return "DEAD";
            default:
                return "Unidentified State";
        }
        return (char*)"Unidentified State";
}