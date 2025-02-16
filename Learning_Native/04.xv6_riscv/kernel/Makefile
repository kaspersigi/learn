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
LLVM = -20
CONFIG = llvm-config$(LLVM)
ARCH = i686-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=riscv64-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LINK_FLAGS = -z max-page-size=4096
LIBS = -lpthread
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-omit-frame-pointer -ffreestanding -fno-common -fno-pic -fno-pie -static -mno-relax -mcmodel=medany

.PHONY : all
all : kernel
kernel : bio.o console.o exec.o file.o fs.o kalloc.o log.o main.o pipe.o plic.o printf.o proc.o sleeplock.o spinlock.o start.o string.o syscall.o sysfile.o sysproc.o trap.o uart.o virtio_disk.o vm.o entry.o kernelvec.o swtch.o trampoline.o initcode
	$(LD) -T kernel.ld -o kernel entry.o start.o console.o printf.o uart.o kalloc.o spinlock.o string.o main.o vm.o proc.o swtch.o trampoline.o trap.o syscall.o sysproc.o bio.o fs.o log.o sleeplock.o file.o pipe.o exec.o sysfile.o kernelvec.o plic.o virtio_disk.o $(LINK_FLAGS)
	rm -v *.o initcode
bio.o : bio.c
	$(CC) bio.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
console.o : console.c
	$(CC) console.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
exec.o : exec.c
	$(CC) exec.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
file.o : file.c
	$(CC) file.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
fs.o : fs.c
	$(CC) fs.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
kalloc.o : kalloc.c
	$(CC) kalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
log.o : log.c
	$(CC) log.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
main.o : main.c
	$(CC) main.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
pipe.o : pipe.c
	$(CC) pipe.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
plic.o : plic.c
	$(CC) plic.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
printf.o : printf.c
	$(CC) printf.c -c $(C_FLAGS) -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static -mcmodel=medany $(DEBUG)
proc.o : proc.c
	$(CC) proc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
sleeplock.o : sleeplock.c
	$(CC) sleeplock.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
spinlock.o : spinlock.c
	$(CC) spinlock.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
start.o : start.c
	$(CC) start.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
string.o : string.c
	$(CC) string.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
syscall.o : syscall.c
	$(CC) syscall.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
sysfile.o : sysfile.c
	$(CC) sysfile.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
sysproc.o : sysproc.c
	$(CC) sysproc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
trap.o : trap.c
	$(CC) trap.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
uart.o : uart.c
	$(CC) uart.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
virtio_disk.o : virtio_disk.c
	$(CC) virtio_disk.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
vm.o : vm.c
	$(CC) vm.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
entry.o : entry.S
	$(CC) entry.S -c -gdwarf-2
kernelvec.o : kernelvec.S
	$(CC) kernelvec.S -c -gdwarf-2
swtch.o : swtch.S
	$(CC) swtch.S -c -gdwarf-2
trampoline.o : trampoline.S
	$(CC) trampoline.S -c -gdwarf-2
initcode : initcode.bin
	$(OBJCOPY) -S -O binary initcode.bin initcode
	rm -v initcode.bin
initcode.bin : initcode.o
	$(LD) -N -e start -Ttext 0 -o initcode.bin initcode.o $(LINK_FLAGS)
	rm -v initcode.o
initcode.o : initcode.S
	$(CC) initcode.S -c -gdwarf-2
format :
	$(FORMAT) bio.c -style=file -i
	$(FORMAT) console.c -style=file -i
	$(FORMAT) exec.c -style=file -i
	$(FORMAT) file.c -style=file -i
	$(FORMAT) fs.c -style=file -i
	$(FORMAT) kalloc.c -style=file -i
	$(FORMAT) log.c -style=file -i
	$(FORMAT) main.c -style=file -i
	$(FORMAT) pipe.c -style=file -i
	$(FORMAT) plic.c -style=file -i
	$(FORMAT) printf.c -style=file -i
	$(FORMAT) proc.c -style=file -i
	$(FORMAT) sleeplock.c -style=file -i
	$(FORMAT) spinlock.c -style=file -i
	$(FORMAT) start.c -style=file -i
	$(FORMAT) string.c -style=file -i
	$(FORMAT) syscall.c -style=file -i
	$(FORMAT) sysfile.c -style=file -i
	$(FORMAT) sysproc.c -style=file -i
	$(FORMAT) trap.c -style=file -i
	$(FORMAT) uart.c -style=file -i
	$(FORMAT) virtio_disk.c -style=file -i
	$(FORMAT) vm.c -style=file -i
clean :
	rm -v kernel