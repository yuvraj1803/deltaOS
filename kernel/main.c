#include "drivers/uart.h"
#include "stdio.h"
#include "kernel/misc.h"

void main(){
    
    uart_init();

    printf("hello threre! %d", get_current_el());
}