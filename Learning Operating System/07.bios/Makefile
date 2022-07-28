###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = loader.bin bios.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
loader.bin : loader.s boot.img
	$(AS) -f bin loader.s -o loader.bin
	dd if=loader.bin of=boot.img count=1 bs=1440k conv=sync
bios.bin : bios.s boot.img
	$(AS) -f bin bios.s -o bios.bin
	dd if=bios.bin of=boot.img count=2880k bs=512 conv=notrunc seek=100
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 1M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc