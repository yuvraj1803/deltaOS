INC = ./include
LIB = ./lib/include
TOOLCHAIN=aarch64-linux-gnu-
CC = 		$(TOOLCHAIN)gcc
AS = 		$(TOOLCHAIN)as
LD = 		$(TOOLCHAIN)ld
OBJCOPY = 	$(TOOLCHAIN)objcopy
OBJDUMP = 	$(TOOLCHAIN)objdump

CFLAGS = -g -ffreestanding -nostdlib -nostartfiles -Wall -I$(INC) -I$(LIB)
ASMFLAGS = -g -I$(INC)

OBJ += ./build/boot/boot.S.o
OBJ += ./build/kernel/main.o

.PHONY: all
all: kernel8.img

./build/kernel/%.o: ./kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

./build/mm/%.o: ./mm/%.c
	$(CC) $(CFLAGS) -c $< -o $@

./build/boot/%.S.o: ./boot/%.S
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/kernel/%.S.o : ./kernel/%.S
	$(CC) $(ASMFLAGS) -c $< -o $@

./build/mm/%.S.o: ./mm/%.S
	$(CC) $(ASMFLAGS) -c $< -o $@	

./build/drivers/%.o: ./drivers/%.c
	$(CC) $(CFLAGS) -c $< -o $@

./build/fs/%.o: ./fs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

./build/lib/%.o: ./lib/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
./build/shell/%.o : ./shell/%.c
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


		
