#include "omegaCOM/omegaCOM.h"
#include <stdint.h>

int8_t __ocom_store_page(uint64_t key, uint64_t page_base_address);
int8_t __ocom_load_page(uint64_t key, uint64_t dest_page_base_address);

int8_t ocom_store_page(uint64_t key, uint64_t page_base_address){

    int8_t ret;

    ret = __ocom_store_page(key, page_base_address);

    return ret;

}

int8_t ocom_load_page(uint64_t key, uint64_t dest_page_base_address){

    int8_t ret;

    ret = __ocom_load_page(key, dest_page_base_address);

    return ret;

}