#include "kernel/process.h"
#include "mm/mm.h"

struct process* process_init(char* name, void* process_function){

}
void prepare_process(){

}
struct pt_regs* get_process_pt_regs(struct process* _process){
    return (struct pt_regs*) ((uint64_t)_process + PAGE_SIZE - sizeof(struct pt_regs));
}
char* process_state_to_string(uint8_t state){
        switch(state){
            case 0:
                return "WAITING";
            case 1:
                return "RUNNING";
            case 2:
                return "DEAD";
            default:
                return "Unidentified State";
        }
        return (char*)"Unidentified State";
}