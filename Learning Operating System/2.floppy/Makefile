###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = floppy.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
floppy.bin : floppy.s boot.img
	$(AS) -f bin floppy.s -o floppy.bin
	dd if=floppy.bin of=boot.img count=1 bs=1440k conv=sync
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc