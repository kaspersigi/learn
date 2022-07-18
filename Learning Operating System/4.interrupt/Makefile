###########################################
#Makefile for my assembler programs
###########################################

TRG = all
OBJ = loader.bin interrupt.bin
AS = nasm

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
loader.bin : loader.s boot.img
	$(AS) -f bin loader.s -o loader.bin
	dd if=loader.bin of=boot.img count=1 bs=1440k conv=sync
interrupt.bin : interrupt.s boot.img
	$(AS) -f bin interrupt.s -o interrupt.bin
	dd if=interrupt.bin of=boot.img count=2880k bs=512 conv=notrunc seek=100
clean :
	rm -v boot.img
qemu :
	qemu-system-x86_64 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 16M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc