/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#include "config.h"

.section ".text.boot"

.globl _start
.globl halt

_start:	
	bl cpu_check 		// we check if we are on the main CPU or not. Otherwise, we just halt
	bl bss_init 		// initialise bss section
			
	ldr x0, =EL1_STACK_BASE
	mov sp, x0

	bl main			// as you can see, we are probably at EL3 or even EL2. 
	b halt			// but it doesnt matter since we are not running under a hypervisor or a secure monitor
					// if we were, they will automatically place us into EL1. So lets not touch any EL2/3 regs here.
cpu_check:
	mrs x0, mpidr_el1
	and x0, x0, 0b11
	cbnz x0, halt
	ret

bss_init:	
	ldr x0, =__bss_start
	ldr x1, =__bss_end
	ldr x2, =0

1:	str x2, [x0]
	add x0, x0, 1
	cmp x0, x1
	ble 1b
	ret


halt:
	wfe
	b halt 
	
