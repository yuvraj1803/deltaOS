/*
 *
 * Copyright (c) 2024 Yuvraj Sakshith <ysakshith@gmail.com>
 *
 */

#ifndef __OMEGA_COM_H__
#define __OMEGA_COM_H__

#include <stdint.h>

int8_t ocom_store_page(uint64_t key, uint64_t page_base_address);
int8_t ocom_load_page(uint64_t key, uint64_t dest_page_base_address);

#endif