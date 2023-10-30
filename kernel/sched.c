#include "kernel/sched.h"
#include "kernel/kthread.h"
#include "stdio.h"
#include "memory.h"
#include "config.h"

extern struct kthread* kthread_list[CONFIG_MAX_KTHREADS];
extern int total_kthreads;

struct kthread* current_kthread; // kthread which is running on CPU currently.

void sched_init(){

    memset(&kthread_list, 0, sizeof(kthread_list));
    total_kthreads = 0;

    log("Scheduler initialised");
}

void scheduler_tick(){
    
}

void schedule(){
    
}