###########################################
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/i686-linux-gnu-as
LD = /usr/bin/i686-linux-gnu-ld
CC = /usr/bin/i686-linux-gnu-gcc
CXX = /usr/bin/g++
LLVM = -19
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -O2
LIBS = -lpthread
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
ARCH = -m32
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static

.PHONY : all
all : xv6.img bootloader.bin kernel.bin
	dd if=bootloader/bootblock of=xv6.img count=1 bs=200k conv=sync
	dd if=kernel/kernel of=xv6.img count=400k bs=512 conv=notrunc seek=1
	$(MAKE) -C filesystem
	mv filesystem/fs.img .
	rm bootloader/bootblock
xv6.img :
	dd if=/dev/zero of=xv6.img count=1 bs=1440k conv=sync
bootloader.bin : bootloader
	$(MAKE) -C bootloader
kernel.bin : kernel
	$(MAKE) -C kernel
format :
	$(FORMAT) include/asm.h -style=file -i
	$(FORMAT) include/buf.h -style=file -i
	$(FORMAT) include/date.h -style=file -i
	$(FORMAT) include/defs.h -style=file -i
	$(FORMAT) include/elf.h -style=file -i
	$(FORMAT) include/fcntl.h -style=file -i
	$(FORMAT) include/file.h -style=file -i
	$(FORMAT) include/fs.h -style=file -i
	$(FORMAT) include/kbd.h -style=file -i
	$(FORMAT) include/memlayout.h -style=file -i
	$(FORMAT) include/mmu.h -style=file -i
	$(FORMAT) include/mp.h -style=file -i
	$(FORMAT) include/param.h -style=file -i
	$(FORMAT) include/proc.h -style=file -i
	$(FORMAT) include/sleeplock.h -style=file -i
	$(FORMAT) include/spinlock.h -style=file -i
	$(FORMAT) include/stat.h -style=file -i
	$(FORMAT) include/syscall.h -style=file -i
	$(FORMAT) include/traps.h -style=file -i
	$(FORMAT) include/types.h -style=file -i
	$(FORMAT) include/x86.h -style=file -i
	$(MAKE) -C bootloader format
	$(MAKE) -C kernel format
clean :
	rm -v xv6.img fs.img
	$(MAKE) -C bootloader clean
	$(MAKE) -C kernel clean
qemu :
	qemu-system-i386 -cpu max -machine pc,accel=tcg,kernel-irqchip=split,hmat=on -smp 4,cores=1,threads=1,sockets=4 -m 256M -drive file=fs.img,index=1,media=disk,format=raw -drive file=xv6.img,index=0,media=disk,format=raw -serial stdio
bochs :
	bochs -f mac.bxrc
smp :
	bochs -f smp.bxrc