#include "kernel/sync.h"
#include <stdint.h>
#include "stdio.h"

void handle_sync(uint64_t esr_el1, uint64_t elr_el1, uint64_t far_el1, uint64_t svc_number){
    printf("sync exc occured\n");
    return;
}