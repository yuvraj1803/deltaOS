#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>

void mmu_init();

void load_ttbr0_el1(uint64_t __page_dir_start);
void load_tcr_el1();
void load_mair_el1();
void enable_mmu();
void disable_mmu();
void prepare_page_tables_and_map_memory(uint64_t __page_dir_start);

struct virtual_address_space{
    uint64_t* lv1_table;
};

#endif