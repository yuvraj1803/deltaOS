#define OCOM_STORE_SMC_NR       0
#define OCOM_LOAD_SMC_NR        1

.globl __ocom_store_page
.globl __ocom_load_page

// __ocom_store_page(key, page_base_address)
// __ocom_load_page(key, dest_page_base_address)
__ocom_store_page:
    mov x2, x1
    mov x1, x0

    smc #OCOM_STORE_SMC_NR
    ret

__ocom_load_page:
    mov x2, x1
    mov x1, x0

    smc #OCOM_LOAD_SMC_NR
    ret
