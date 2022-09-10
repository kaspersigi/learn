###########################################
#Makefile for my assembler programs
###########################################
TRG = all
OBJ = boot.bin head.bin kernel.bin program.bin
AS = /usr/bin/as
LD = /usr/bin/ld

.PHONY : all
$(TRG) : $(OBJ) boot.img
	rm -v $(OBJ)
boot.img :
	dd if=/dev/zero of=boot.img count=1 bs=1440k conv=sync
boot.bin : boot.s boot.img
	$(AS) boot.s -o boot.o
	$(LD) boot.o -Ttext 0x7c00 -s --oformat binary -o boot.bin
	rm -v boot.o
	dd if=boot.bin of=boot.img count=1 bs=1440k conv=sync
head.bin : head.s boot.img
	$(AS) head.s -o head.o
	$(LD) head.o -o head.bin -T head.lds
	rm -v head.o
	dd if=head.bin of=boot.img count=2880k bs=512 conv=notrunc seek=1
kernel.bin : kernel.s boot.img
	$(AS) kernel.s -o kernel.o
	$(LD) kernel.o -Ttext 0x00 -s --oformat binary -o kernel.bin
	rm -v kernel.o
	dd if=kernel.bin of=boot.img count=2880k bs=512 conv=notrunc seek=4
program.bin : program.s boot.img
	$(AS) program.s -o program.o
	$(LD) program.o -Ttext 0x00 -s --oformat binary -o program.bin
	rm -v program.o
	dd if=program.bin of=boot.img count=2880k bs=512 conv=notrunc seek=100
clean :
	rm -v boot.img
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 1,cores=1,threads=1,sockets=1 -m 2M -drive format=raw,file=./boot.img
bochs :
	bochs -f ../mac.bxrc