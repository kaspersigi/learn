###########################################
#Makefile for my C programs
###########################################
TRG = all
EXEC = main
BIN = main.bin
OBJ = main.o
SRC = main.s
AS = /usr/bin/riscv64-linux-gnu-as
LD = /usr/bin/riscv64-linux-gnu-ld
OBJCOPY = /usr/bin/riscv64-linux-gnu-objcopy
LLVM = -19
CONFIG = llvm-config$(LLVM)
ARCH = i386-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=riscv64-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LINK_FLAGS = -z max-page-size=4096
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-omit-frame-pointer -ffreestanding -fno-common -fno-pic -fno-pie -static -mno-relax -mcmodel=medany

.PHONY : all
all :
	$(MAKE) -C filesystem
	$(MAKE) -C kernel
format :
	$(FORMAT) include/buf.h -style=file -i
	$(FORMAT) include/defs.h -style=file -i
	$(FORMAT) include/elf.h -style=file -i
	$(FORMAT) include/fcntl.h -style=file -i
	$(FORMAT) include/file.h -style=file -i
	$(FORMAT) include/fs.h -style=file -i
	$(FORMAT) include/memlayout.h -style=file -i
	$(FORMAT) include/param.h -style=file -i
	$(FORMAT) include/proc.h -style=file -i
	$(FORMAT) include/riscv.h -style=file -i
	$(FORMAT) include/sleeplock.h -style=file -i
	$(FORMAT) include/spinlock.h -style=file -i
	$(FORMAT) include/stat.h -style=file -i
	$(FORMAT) include/syscall.h -style=file -i
	$(FORMAT) include/types.h -style=file -i
	$(FORMAT) include/virtio.h -style=file -i
	$(MAKE) -C kernel format
	$(MAKE) -C filesystem format
clean :
	$(MAKE) -C kernel clean
	$(MAKE) -C filesystem clean
qemu :
	qemu-system-riscv64 -machine virt -bios none -kernel kernel/kernel -m 128M -smp 4 -global virtio-mmio.force-legacy=false -drive file=filesystem/fs.img,if=none,format=raw,id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 -nographic