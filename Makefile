INC = ./include 
LIB = ./lib/include
SSE = ./deltaSSE
TOOLCHAIN=@aarch64-linux-gnu-
CC = 		$(TOOLCHAIN)gcc
AS = 		$(TOOLCHAIN)as
LD = 		$(TOOLCHAIN)ld
OBJCOPY = 	$(TOOLCHAIN)objcopy
OBJDUMP = 	$(TOOLCHAIN)objdump

CFLAGS = -g -ffreestanding -nostdlib -nostartfiles -Wall -I$(INC) -I$(LIB) -I$(SSE) -mgeneral-regs-only
ASMFLAGS = -g -I$(INC)

OBJ += ./build/boot/boot.S.o
OBJ += ./build/kernel/main.o
OBJ += ./build/kernel/misc.S.o
OBJ += ./build/kernel/irq.S.o
OBJ += ./build/kernel/irq.o
OBJ += ./build/kernel/exceptions.S.o
OBJ += ./build/kernel/sync.o
OBJ += ./build/kernel/kthread.o
OBJ += ./build/kernel/sched.o
OBJ += ./build/drivers/uart.o
OBJ += ./build/drivers/timer.o
OBJ += ./build/deltaSSE/sse.S.o
OBJ += ./build/mm/mm.o
OBJ += ./build/mm/mm.S.o
OBJ += ./build/mm/paging.S.o
OBJ += ./build/mm/paging.o
OBJ += ./build/lib/memory.o
OBJ += ./build/lib/stdio.o
OBJ += ./build/lib/stdlib.o
OBJ += ./build/lib/string.o
OBJ += ./build/shell/shell.o

.PHONY: all
all: kernel8.img

./build/kernel/%.o: ./kernel/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.o: ./mm/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/boot/%.S.o: ./boot/%.S
	@echo [compiling] $@
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/kernel/%.S.o : ./kernel/%.S
	@echo [compiling] $@
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/mm/%.S.o: ./mm/%.S
	@echo [compiling] $@
	$(CC) $(ASMFLAGS) -c $< -o $@	

./build/drivers/%.o: ./drivers/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/fs/%.o: ./fs/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/lib/%.o: ./lib/src/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@
./build/shell/%.o : ./shell/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@

./build/deltaSSE/%.S.o: ./deltaSSE/%.S
	@echo [compiling] $@
	$(CC) $(ASMFLAGS) -c $< -o $@	

./build/shell/%.o: ./shell/%.c
	@echo [compiling] $@
	$(CC) $(CFLAGS) -c $< -o $@	


kernel8.img : $(OBJ)
	$(LD) -T linker.ld -o ./deltaOS.elf $(OBJ_C) $(OBJ)
	$(OBJCOPY) ./deltaOS.elf -O binary ./kernel8.img


.PHONY: run
run: kernel8.img qemu

.PHONY: debug
debug: kernel8.img 
	qemu-system-aarch64 -M raspi3b -nographic -serial null -serial mon:stdio -m 1024 -kernel ./kernel8.img -s -S

.PHONY: qemu
qemu: 
	qemu-system-aarch64 -M raspi3b -nographic -serial null -serial mon:stdio -m 1024 -kernel ./kernel8.img

.PHONY: objdump
objdump: kernel8.img
	$(OBJDUMP) -D deltaOS.elf > deltaOS.list

.PHONY: clean
clean:
	rm -f *.elf
	rm -f *.img
	find ./build -name '*.o' -delete 
	find ./build -name '*.d' -delete
	rm -rf *.list


		
