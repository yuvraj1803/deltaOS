#include "drivers/uart.h"
#include "drivers/timer.h"
#include "stdio.h"
#include "kernel/misc.h"
#include "kernel/irq.h"

void main(){
    
    uart_init();
    timer_init();
    interrupt_controller_init();

    printf("hello threre!");
}