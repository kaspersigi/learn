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
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = i386-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=riscv64-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -ggdb -O0
RELEASE = -static -Oz
LINK_FLAGS = -z max-page-size=4096
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
KERNEL_FLAGS = -nostdinc -fno-builtin -fno-omit-frame-pointer -ffreestanding -fno-common -fno-pic -fno-pie -static -mno-relax -mcmodel=medany

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
	$(LD) cat.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _cat $(LINK_FLAGS)
	rm -v cat.o
_echo : echo.c _common
	$(CC) echo.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) echo.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _echo $(LINK_FLAGS)
	rm -v echo.o
_forktest : forktest.c _common
	$(CC) forktest.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) forktest.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _forktest $(LINK_FLAGS)
	rm -v forktest.o
_grep : grep.c _common
	$(CC) grep.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) grep.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _grep $(LINK_FLAGS)
	rm -v grep.o
_init : init.c _common
	$(CC) init.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) init.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _init $(LINK_FLAGS)
	rm -v init.o
_kill : kill.c _common
	$(CC) kill.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) kill.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _kill $(LINK_FLAGS)
	rm -v kill.o
_ln : ln.c _common
	$(CC) ln.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) ln.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _ln $(LINK_FLAGS)
	rm -v ln.o
_ls : ls.c _common
	$(CC) ls.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) ls.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _ls $(LINK_FLAGS)
	rm -v ls.o
_mkdir : mkdir.c _common
	$(CC) mkdir.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) mkdir.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _mkdir $(LINK_FLAGS)
	rm -v mkdir.o
_rm : rm.c _common
	$(CC) rm.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) rm.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _rm $(LINK_FLAGS)
	rm -v rm.o
_sh : sh.c _common
	$(CC) sh.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) sh.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _sh $(LINK_FLAGS)
	rm -v sh.o
_stressfs : stressfs.c _common
	$(CC) stressfs.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) stressfs.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _stressfs $(LINK_FLAGS)
	rm -v stressfs.o
_usertests : usertests.c _common
	$(CC) usertests.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) usertests.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _usertests $(LINK_FLAGS)
	rm -v usertests.o
_wc : wc.c _common
	$(CC) wc.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) wc.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _wc $(LINK_FLAGS)
	rm -v wc.o
_zombie : zombie.c _common
	$(CC) zombie.c -c $(C_FLAGS) $(KERNEL_FLAGS) $(DEBUG)
	$(LD) zombie.o -T user.ld common/ulib.o common/usys.o common/printf.o common/umalloc.o -o _zombie $(LINK_FLAGS)
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