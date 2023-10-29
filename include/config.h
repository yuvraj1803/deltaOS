/*
 *
 * Copyright (c) 2023 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */


#ifndef __config_h__
#define __config_h__

#define CONFIG_SCHED_QUANTA     100         // in milliseconds

#define EL1_STACK_BASE		0x80000 - 0x1

#define EL1_SCTLR_NO_MMU		0
#define EL1_SCTLR_WITH_MMU	EL1_SCTLR_NO_MMU | (1 << 0)

#define EL1_TCR	   /*T0SZ*/	(64-48) | /*4K TG0*/	(0 << 14) | /*T1SZ*/ ((64-48)<<16) | /*4K TG1*/ (2 << 30)

#endif
