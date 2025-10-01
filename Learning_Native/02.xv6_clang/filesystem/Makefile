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
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = i686-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=i686-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-strict-aliasing -fno-omit-frame-pointer -fno-stack-protector -fno-pic -fno-pie -static

.PHONY : all
all : mkfs _cat _echo _forktest _grep _init _kill _ln _ls _mkdir _rm _sh _stressfs _usertests _wc _zombie
	./mkfs fs.img README _cat _echo _forktest _grep _init _kill _ln _ls _mkdir _rm _sh _stressfs _usertests _wc _zombie
	$(MAKE) -C common clean
	rm -v mkfs _cat _echo _forktest _grep _init _kill _ln _ls _mkdir _rm _sh _stressfs _usertests _wc _zombie
mkfs : mkfs.o
	/usr/bin/clang$(LLVM) mkfs.o -o mkfs
	rm -v mkfs.o
mkfs.o : mkfs.c
	/usr/bin/clang$(LLVM) mkfs.c -c $(C_FLAGS) $(DEBUG)
_cat : cat.c _common
	$(CC) cat.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) cat.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _cat -N -e main -Ttext 0x0 -m elf_i386
	rm -v cat.o
_echo : echo.c _common
	$(CC) echo.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) echo.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _echo -N -e main -Ttext 0x0 -m elf_i386
	rm -v echo.o
_forktest : forktest.c _common
	$(CC) forktest.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) forktest.o common/ulib.o common/usys.o -o _forktest -N -e main -Ttext 0x0 -m elf_i386
	rm -v forktest.o
_grep : grep.c _common
	$(CC) grep.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) grep.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _grep -N -e main -Ttext 0x0 -m elf_i386
	rm -v grep.o
_init : init.c _common
	$(CC) init.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) init.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _init -N -e main -Ttext 0x0 -m elf_i386
	rm -v init.o
_kill : kill.c _common
	$(CC) kill.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) kill.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _kill -N -e main -Ttext 0x0 -m elf_i386
	rm -v kill.o
_ln : ln.c _common
	$(CC) ln.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) ln.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _ln -N -e main -Ttext 0x0 -m elf_i386
	rm -v ln.o
_ls : ls.c _common
	$(CC) ls.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) ls.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _ls -N -e main -Ttext 0x0 -m elf_i386
	rm -v ls.o
_mkdir : mkdir.c _common
	$(CC) mkdir.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) mkdir.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _mkdir -N -e main -Ttext 0x0 -m elf_i386
	rm -v mkdir.o
_rm : rm.c _common
	$(CC) rm.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) rm.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _rm -N -e main -Ttext 0x0 -m elf_i386
	rm -v rm.o
_sh : sh.c _common
	$(CC) sh.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) sh.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _sh -N -e main -Ttext 0x0 -m elf_i386
	rm -v sh.o
_stressfs : stressfs.c _common
	$(CC) stressfs.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) stressfs.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _stressfs -N -e main -Ttext 0x0 -m elf_i386
	rm -v stressfs.o
_usertests : usertests.c _common
	$(CC) usertests.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) usertests.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _usertests -N -e main -Ttext 0x0 -m elf_i386
	rm -v usertests.o
_wc : wc.c _common
	$(CC) wc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) wc.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _wc -N -e main -Ttext 0x0 -m elf_i386
	rm -v wc.o
_zombie : zombie.c _common
	$(CC) zombie.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) zombie.o common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _zombie -N -e main -Ttext 0x0 -m elf_i386
	rm -v zombie.o
_common : common
	$(MAKE) -C common
format :
	$(MAKE) -C common format
	$(FORMAT) include/user.h -style=file -i
	$(FORMAT) mkfs.c -style=file -i
	$(FORMAT) cat.c -style=file -i
	$(FORMAT) echo.c -style=file -i
	$(FORMAT) forktest.c -style=file -i
	$(FORMAT) grep.c -style=file -i
	$(FORMAT) init.c -style=file -i
	$(FORMAT) kill.c -style=file -i
	$(FORMAT) ln.c -style=file -i
	$(FORMAT) ls.c -style=file -i
	$(FORMAT) mkdir.c -style=file -i
	$(FORMAT) rm.c -style=file -i
	$(FORMAT) sh.c -style=file -i
	$(FORMAT) stressfs.c -style=file -i
	$(FORMAT) usertests.c -style=file -i
	$(FORMAT) wc.c -style=file -i
	$(FORMAT) zombie.c -style=file -i
clean :
	rm -v fs.img