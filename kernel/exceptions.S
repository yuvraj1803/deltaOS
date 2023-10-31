#include "kernel/exceptions.h"

.macro kernel_entry
    // we pull back sp by 8*34 addresses because 34 registers needs to be pushed
    sub sp, sp, #8*34
    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]

    add x21, sp, #8*34
    mrs x22, elr_el1
    mrs x23, spsr_el1
    stp x30, x21, [sp, #16 * 15]
    stp x22, x23, [sp, #16 * 16]
.endm

.macro kernel_exit
    ldp x30, x21, [sp, #16 * 15]
    ldp x22, x23, [sp, #16 * 16]

    msr elr_el1, x22
    msr spsr_el1, x23
    ldp x0, x1, [sp, #16 * 0]
    ldp x2, x3, [sp, #16 * 1]
    ldp x4, x5, [sp, #16 * 2]
    ldp x6, x7, [sp, #16 * 3]
    ldp x8, x9, [sp, #16 * 4]
    ldp x10, x11, [sp, #16 * 5]
    ldp x12, x13, [sp, #16 * 6]
    ldp x14, x15, [sp, #16 * 7]
    ldp x16, x17, [sp, #16 * 8]
    ldp x18, x19, [sp, #16 * 9]
    ldp x20, x21, [sp, #16 * 10]
    ldp x22, x23, [sp, #16 * 11]
    ldp x24, x25, [sp, #16 * 12]
    ldp x26, x27, [sp, #16 * 13]
    ldp x28, x29, [sp, #16 * 14]
    add sp, sp, #8*34
    ret
.endm

.macro handle_unsupported_interrupt interrupt_type
//	kernel_entry
	mov x0, #\interrupt_type
	mrs x1, esr_el1
	mrs x2, elr_el1
	mrs x3, far_el1
	bl log_unsupported_exception
	b halt 
.endm

.macro ventry handler
.align 7
    b \handler
.endm

.macro handle_irq_interrupt
//	kernel_entry
	bl handle_irq
//	kernel_exit
.endm

/*
.macro handle_sync_interrupt    // This interrupt will always come from EL0, so there is no point of having 'el' arg.
                                // I have added it just to make it more readable.
	kernel_entry \el
    mrs x0, esr_el1
    mrs x1, elr_el1
    mrs x2, far_el1
    mov x3, x8      // supervisor call (svc) number.
	bl handle_sync
	kernel_exit \el
.endm
*/

.align 11
.globl vtable
vtable:
	ventry current_el_sp0_sync
	ventry current_el_sp0_irq
	ventry current_el_sp0_fiq
	ventry current_el_sp0_serror

	ventry current_el_spx_sync
	ventry current_el_spx_irq
	ventry current_el_spx_fiq
	ventry current_el_spx_serror

	ventry lower_el_a64_sync
	ventry lower_el_a64_irq
	ventry lower_el_a64_fiq
	ventry lower_el_a64_serror
	
	ventry lower_el_a32_sync
	ventry lower_el_a32_irq
	ventry lower_el_a32_fiq
	ventry lower_el_a32_serror

 current_el_sp0_sync:
 	handle_unsupported_interrupt  CURRENT_EL_SP0_SYNC 	
 current_el_sp0_irq:
  	handle_unsupported_interrupt  CURRENT_EL_SP0_IRQ
 current_el_sp0_fiq:
  	handle_unsupported_interrupt  CURRENT_EL_SP0_FIQ
 current_el_sp0_serror:
  	handle_unsupported_interrupt  CURRENT_EL_SP0_SERROR

 current_el_spx_sync:
  	handle_unsupported_interrupt  CURRENT_EL_SPX_SYNC
 current_el_spx_irq:
  	handle_irq_interrupt
 current_el_spx_fiq:
  	handle_unsupported_interrupt  CURRENT_EL_SPX_FIQ
 current_el_spx_serror:
  	handle_unsupported_interrupt  CURRENT_EL_SPX_SERROR

 lower_el_a64_sync:
  	handle_unsupported_interrupt  LOWER_EL_A64_SYNC
 lower_el_a64_irq:
  	handle_unsupported_interrupt  LOWER_EL_A64_IRQ
 lower_el_a64_fiq:
  	handle_unsupported_interrupt  LOWER_EL_A64_FIQ
 lower_el_a64_serror:
  	handle_unsupported_interrupt  LOWER_EL_A64_SERROR

 lower_el_a32_sync:
  	handle_unsupported_interrupt  LOWER_EL_A32_SYNC
 lower_el_a32_irq:
  	handle_unsupported_interrupt  LOWER_EL_A32_IRQ
 lower_el_a32_fiq:
  	handle_unsupported_interrupt  LOWER_EL_A32_FIQ
 lower_el_a32_serror:
  	handle_unsupported_interrupt  LOWER_EL_A32_SERROR









