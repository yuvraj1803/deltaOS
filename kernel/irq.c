/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "kernel/irq.h"
#include "mm/mm.h"
#include <stdint.h>
#include "stdio.h"
#include "drivers/timer.h"
#include "kernel/misc.h"
#include "drivers/uart.h"

const char* exception_info[] = {
	"CURRENT_EL_SP0_SYNC",
	"CURRENT_EL_SP0_IRQ",
	"CURRENT_EL_SP0_FIQ",
	"CURRENT_EL_SP0_SERROR",
	
	"CURRENT_EL_SPX_SYNC",
	"CURRENT_EL_SPX_IRQ",
	"CURRENT_EL_SPX_FIQ",
	"CURRENT_EL_SPX_SERROR",
	
	"LOWER_EL_A64_SYNC",
	"LOWER_EL_A64_IRQ",
	"LOWER_EL_A64_FIQ",
	"LOWER_EL_A64_SERROR",
	
	"LOWER_EL_A32_SYNC",
	"LOWER_EL_A32_IRQ",
	"LOWER_EL_A32_FIQ",
	"LOWER_EL_A32_SERROR"
};

// refer to bcm2835 reference manual for more details about these constants

#define SYSTEM_TIMER_MATCH_1		(1U << 1)
#define SYSTEM_TIMER_MATCH_3		(1U << 3)
#define AUX_INT				        (1U << 29)
#define FIQ_ENABLE			        (1U << 7)


void interrupt_controller_init(){
	mm_w32(FIQ_CONTROL, 0xc1);
	mm_w32(ENABLE_IRQs_1, SYSTEM_TIMER_MATCH_1);
	mm_w32(ENABLE_IRQs_1, SYSTEM_TIMER_MATCH_3);
    mm_w32(ENABLE_IRQs_1, AUX_INT);

	log("IRQ initialised");
	log("Interrupt Controller initialised");

}

void log_unsupported_exception(uint64_t exception_type,
			       uint64_t esr_el1,
			       uint64_t elr_el1,
			       uint64_t far_el1){

	printf("[UNCAUGHT EXCEPTION] : %s [ESR_EL1] : %x [ELR_EL1] : %x [FAR_EL1] : %x\n", exception_info[exception_type], esr_el1, elr_el1, far_el1, exception_type > 7 ? get_current_el() -1 : get_current_el());
}


void handle_irq(){

	uint32_t pending = mm_r32(IRQ_PENDING_1);

	if(pending & SYSTEM_TIMER_MATCH_1) system_timer_1_handler();
	else{
		panic("Unknown IRQ Pending.");
	}


}
