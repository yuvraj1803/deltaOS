#ifndef __SYNC_H__
#define __SYNC_H__

#include <stdint.h>

void handle_sync(uint64_t esr_el1, uint64_t elr_el1, uint64_t far_el1, uint64_t svc_number);

#endif