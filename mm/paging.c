#include "mm/paging.h"
#include <stdint.h>
#include "stdio.h"

extern volatile uint64_t __page_dir_start;

void mmu_init(){
    prepare_page_tables_and_map_memory((uint64_t)&__page_dir_start);
	load_ttbr0_el1(((uint64_t)(uint64_t*)&__page_dir_start));
	load_tcr_el1();
	load_mair_el1();
	enable_mmu();
	
	log("MMU initialised"); 
}