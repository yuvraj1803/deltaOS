#include "drivers/uart.h"
#include "drivers/timer.h"
#include "stdio.h"
#include "kernel/misc.h"
#include "kernel/irq.h"
#include "mm/mm.h"
#include "mm/paging.h"

void main(){

    __disable_irq();

    mmu_init();
    heap_init();    
    uart_init();
    irq_init();
    interrupt_controller_init();
    timer_init();
    
    printf("hello threre!");

    while(1);
}