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
			
	mrs x0, currentel       // we need to check which EL we are in
	lsr x0, x0, 2

	cmp x0, 3		// if we are in EL3, jump to el3_entry
	beq el3_entry

	cmp x0, 2		// if we are in EL2, jump to el2_entry
	beq el2_entry

	cmp x0, 1		// if we are in EL1, jump to el1_entry
	beq el1_entry

	cmp x0, 0		// if we are in EL0, we cant help it. gotta halt.
	b halt

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

el3_entry:
	eret				// jump to el2
	
el2_entry:

	adr x0, el1_entry
	msr elr_el2, x0
	eret				// jump to el1

el1_entry:
	
	ldr x0, =EL1_STACK_BASE
	mov sp, x0

	bl main
	b halt


halt:
	wfe
	b halt 
	
