#include "drivers/uart.h"
#include "drivers/timer.h"
#include "stdio.h"
#include "kernel/misc.h"

void main(){
    
    uart_init();
    timer_init();

    printf("hello threre!");
}