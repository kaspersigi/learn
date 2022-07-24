###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = mbr.bin kernel.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
mbr.bin : mbr.s boot.img
	$(AS) -f bin mbr.s -o mbr.bin
	dd if=mbr.bin of=boot.img count=1 bs=1440k conv=sync
kernel.bin : kernel.s boot.img
	$(AS) -f bin kernel.s -o kernel.bin
	dd if=kernel.bin of=boot.img count=2880k bs=512 conv=notrunc seek=1
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc