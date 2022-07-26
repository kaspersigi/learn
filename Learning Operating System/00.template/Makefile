###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = main.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
main.bin : main.s boot.img
	$(AS) -f bin main.s -o main.bin
	dd if=main.bin of=boot.img count=1 bs=1440k conv=sync
clean :
	rm -v boot.img
qemu :
	qemu-system-x86_64 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 16M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc