###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = sort.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
sort.bin : sort.s boot.img
	$(AS) -f bin sort.s -o sort.bin
	dd if=sort.bin of=boot.img count=1 bs=1440k conv=sync
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc