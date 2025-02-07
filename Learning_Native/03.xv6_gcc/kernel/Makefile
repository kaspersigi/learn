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
C_FLAGS = -std=c2x -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LIBS = -lpthread
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
ARCH = -m32
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static

.PHONY : all
all : kernel
kernel : bio.o console.o exec.o file.o fs.o ide.o ioapic.o kalloc.o kbd.o lapic.o log.o main.o mp.o picirq.o pipe.o proc.o sleeplock.o spinlock.o string.o syscall.o sysfile.o sysproc.o trap.o uart.o vm.o entry.o swtch.o trapasm.o vectors.o initcode entryother
	$(LD) entry.o bio.o console.o exec.o file.o fs.o ide.o ioapic.o kalloc.o kbd.o lapic.o log.o main.o mp.o picirq.o pipe.o proc.o sleeplock.o spinlock.o string.o swtch.o syscall.o sysfile.o sysproc.o trapasm.o trap.o uart.o vectors.o vm.o -o kernel -T kernel.ld -b binary initcode entryother
	rm -v bio.o console.o exec.o file.o fs.o ide.o ioapic.o kalloc.o kbd.o lapic.o log.o main.o mp.o picirq.o pipe.o proc.o sleeplock.o spinlock.o string.o syscall.o sysfile.o sysproc.o trap.o uart.o vm.o entry.o swtch.o trapasm.o vectors.o initcode entryother
bio.o : bio.c
	$(CC) bio.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
console.o : console.c
	$(CC) console.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
exec.o : exec.c
	$(CC) exec.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
file.o : file.c
	$(CC) file.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
fs.o : fs.c
	$(CC) fs.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
ide.o : ide.c
	$(CC) ide.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
ioapic.o : ioapic.c
	$(CC) ioapic.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
kalloc.o : kalloc.c
	$(CC) kalloc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
kbd.o : kbd.c
	$(CC) kbd.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
lapic.o : lapic.c
	$(CC) lapic.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
log.o : log.c
	$(CC) log.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
main.o : main.c
	$(CC) main.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
mp.o : mp.c
	$(CC) mp.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
picirq.o : picirq.c
	$(CC) picirq.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
pipe.o : pipe.c
	$(CC) pipe.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
proc.o : proc.c
	$(CC) proc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
sleeplock.o : sleeplock.c
	$(CC) sleeplock.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
spinlock.o : spinlock.c
	$(CC) spinlock.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
string.o : string.c
	$(CC) string.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
syscall.o : syscall.c
	$(CC) syscall.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
sysfile.o : sysfile.c
	$(CC) sysfile.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
sysproc.o : sysproc.c
	$(CC) sysproc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
trap.o : trap.c
	$(CC) trap.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
uart.o : uart.c
	$(CC) uart.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
vm.o : vm.c
	$(CC) vm.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
entry.o : entry.S
	$(CC) entry.S -c -gdwarf-2 -Wa,-divide $(ARCH)
swtch.o : swtch.S
	$(CC) swtch.S -c -gdwarf-2 -Wa,-divide $(ARCH)
trapasm.o : trapasm.S
	$(CC) trapasm.S -c -gdwarf-2 -Wa,-divide $(ARCH)
vectors.o : vectors.pl
	./vectors.pl > vectors.S
	$(CC) vectors.S -c -gdwarf-2 -Wa,-divide $(ARCH)
	rm -v vectors.S
initcode : initcode.bin
	i686-linux-gnu-objcopy initcode.bin -S -O binary initcode
	rm -v initcode.bin
initcode.bin : initcode.o
	$(LD) initcode.o -o initcode.bin -N -e start -Ttext 0x0 -m elf_i386
	rm -v initcode.o
initcode.o : initcode.S
	$(CC) initcode.S -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
entryother : entryother.bin
	i686-linux-gnu-objcopy entryother.bin -S -O binary -j .text entryother
	rm -v entryother.bin
entryother.bin : entryother.o
	$(LD) entryother.o -o entryother.bin -N -e start -Ttext 0x7000 -m elf_i386
	rm -v entryother.o
entryother.o : entryother.S
	$(CC) entryother.S -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG) $(ARCH)
format :
	$(FORMAT) bio.c -style=file -i
	$(FORMAT) console.c -style=file -i
	$(FORMAT) exec.c -style=file -i
	$(FORMAT) file.c -style=file -i
	$(FORMAT) fs.c -style=file -i
	$(FORMAT) ide.c -style=file -i
	$(FORMAT) ioapic.c -style=file -i
	$(FORMAT) kalloc.c -style=file -i
	$(FORMAT) kbd.c -style=file -i
	$(FORMAT) lapic.c -style=file -i
	$(FORMAT) log.c -style=file -i
	$(FORMAT) main.c -style=file -i
	$(FORMAT) mp.c -style=file -i
	$(FORMAT) picirq.c -style=file -i
	$(FORMAT) pipe.c -style=file -i
	$(FORMAT) proc.c -style=file -i
	$(FORMAT) sleeplock.c -style=file -i
	$(FORMAT) spinlock.c -style=file -i
	$(FORMAT) string.c -style=file -i
	$(FORMAT) syscall.c -style=file -i
	$(FORMAT) sysfile.c -style=file -i
	$(FORMAT) sysproc.c -style=file -i
	$(FORMAT) trap.c -style=file -i
	$(FORMAT) uart.c -style=file -i
	$(FORMAT) vm.c -style=file -i
clean :
	rm -v kernel