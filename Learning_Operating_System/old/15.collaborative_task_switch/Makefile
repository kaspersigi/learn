###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = boot.bin head.bin kernel.bin program.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
boot.bin : boot.s boot.img
	$(AS) -f bin boot.s -o boot.bin
	dd if=boot.bin of=boot.img count=1 bs=1440k conv=sync
head.bin : head.s boot.img
	$(AS) -f bin head.s -o head.bin
	dd if=head.bin of=boot.img count=2880k bs=512 conv=notrunc seek=1
kernel.bin : kernel.s boot.img
	$(AS) -f bin kernel.s -o kernel.bin
	dd if=kernel.bin of=boot.img count=2880k bs=512 conv=notrunc seek=4
program.bin : program.s boot.img
	$(AS) -f bin program.s -o program.bin
	dd if=program.bin of=boot.img count=2880k bs=512 conv=notrunc seek=100
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 2M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc