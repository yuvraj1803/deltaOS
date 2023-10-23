/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __IRQ_H__
#define __IRQ_H__ 

#include <stdint.h>


void irq_init();
void __disable_irq();
void __enable_irq();
void handle_irq();
void log_unsupported_exception(uint64_t exception_type, uint64_t esr_el1, uint64_t elr_el1, uint64_t far_el1);
void interrupt_controller_init();

#endif
