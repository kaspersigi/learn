###########################################
#Makefile for my assembler programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/as
LD = /usr/bin/ld

.PHONY : all
$(TRG) : $(BIN) boot.img
	rm -v $(BIN)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
$(BIN) : main.s boot.img
	$(AS) $(SRC) -o $(OBJ) --32
	$(LD) $(OBJ) -o $(BIN) -T main.lds
	rm -v $(OBJ)
	dd if=main.bin of=boot.img count=1 bs=1440k conv=sync
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc
