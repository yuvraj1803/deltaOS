#include "config.h"
#include "mm/mmu.h"

.globl load_ttbr0_el1
.globl load_tcr_el1
.globl load_mair_el1
.globl enable_mmu
.globl disable_mmu
.globl prepare_page_tables_and_map_memory

prepare_page_tables_and_map_memory:
    // this is for the PAGE GLOBAL DIRECTORY (PGD)
    // __page_dir_start will be passed in x0

    add x1, x0, #PAGE_SIZE
    orr x1, x1, #MMU_TABLE_ENTRY_FLAG
    str x1, [x0]
    
    add x0, x0, #PAGE_SIZE

    // this is for the PAGE MIDDLE DIRECTORY (PMD)
    add x1, x0, #PAGE_SIZE
    orr x1, x1, #MMU_TABLE_ENTRY_FLAG
    str x1, [x0]

    add x0, x0, #PAGE_SIZE

    // this is for the PAGE UPPER DIRECTORY (PUD)
    add x1, x0, #PAGE_SIZE
    orr x1, x1, #MMU_TABLE_ENTRY_FLAG
    str x1, [x0]

    // after this, PGD which is at __page_dir_start will point
    // at the next page, which is nothing but the PUD.
    // NOTE: each page can hold 512 8-byte entries
    // hence PGD and PUD are just 1 page big.

    // Now we identity map OS memory
    // here we will be mapping 2MB blocks directly.
    // There is no point of going down one more level
    // and mapping 4KB blocks.
    ldr x1, =0                       // start of physical address
    ldr x2, =0                       // start of virtual address
    ldr x3, = 0x3F000000 - 0x200000 // end of virtual address
    // here I am subtracting
    // this is being done to not 
    // map MMIO region with wrong flags (overlapping with 0x3F000000).
    lsr x3, x3, 21 // 9 bits for 512 byte PUD and 12 bits for 4KB page
    mov x4, MMU_OS_MEM_FLAGS
    orr x1, x1, x4

1:      str x1, [x0, x2, lsl #3]
    add x2, x2, #1
    add x1, x1, 0x200000 // advance by 2MB
    cmp x2, x3
    b.ls 1b

    // Now we will identity map MMIO section.
    // from 0x3F000000 to 0x40000000 - 2MB
    // same process as before
    ldr x1, =0x3F000000      // MMIO Base
    ldr x2, =0x3F000000
    ldr x3, =0x40000000 - 0x200000  // 0x40000000 because
                                    // RASPI3B has only 1GB of RAM
    lsr x1, x1, 21
    lsr x2, x2, 21
    lsr x3, x3, 21
    mov x4, MMU_OS_MMIO_FLAGS
    orr x1, x4, x1, lsl 21 // (9 + 12)
1:
    str x1, [x0, x2, lsl 3]
    add x2, x2, 1
    add x1, x1, 0x200000 // advance by 2MB
    cmp x2, x3
    b.ls 1b

	ret

load_ttbr0_el1:
    msr ttbr0_el1, x0
    ret

load_tcr_el1:
    ldr x0, =(EL1_TCR)
    msr tcr_el1, x0
	ret

load_mair_el1:
    ldr x0, =(EL1_MAIR)
    msr mair_el1, x0
	ret

enable_mmu:
    ldr x1, =(EL1_SCTLR_WITH_MMU)
    dsb ish
    isb
    msr sctlr_el1, x1        
    isb
	ret

disable_mmu:
	ldr x1, =(EL1_SCTLR_NO_MMU)  
    dsb ish
    isb
    msr sctlr_el1, x1
    isb
	ret


