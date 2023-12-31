#include "drivers/timer.h"
#include "kernel/sched.h"
#include "mm/mm.h"
#include "stdio.h"

const uint32_t timer_interval = (1000000/1000); // timer runs at 1MHz
// (1000000/1000) is number of cycles in 1 ms)


void timer_info(){
	printf("CS: %x\n", mm_r32(TIMER_CS));
	printf("CLO: %x\n", mm_r32(TIMER_CLO));
	printf("CHI: %x\n", mm_r32(TIMER_CHI));
}
void timer_init(void){
	mm_w32(TIMER_C1,mm_r32(TIMER_CLO) + timer_interval);

	log("Timer initialised");
}

void system_timer_1_handler(){

	mm_w32(TIMER_C1,  mm_r32(TIMER_CLO) + timer_interval);
	mm_w32(TIMER_CS, TIMER_CS_M1);
	scheduler_tick();
}