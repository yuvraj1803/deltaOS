#include "drivers/uart.h"
#include "drivers/timer.h"
#include "stdio.h"
#include "kernel/misc.h"
#include "kernel/irq.h"
#include "kernel/sched.h"
#include "mm/mm.h"
#include "mm/paging.h"
#include "shell/shell.h"
#include "sse.h"

void main(){

    __disable_irq();

    uart_init();
    mmu_init();
    heap_init();    
    irq_init();
    interrupt_controller_init();
    timer_init();
    shell_init();


    while(1) shell_run();

}
