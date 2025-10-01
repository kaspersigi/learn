###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o func.o
SRC = main.c
AS = /usr/bin/i686-linux-gnu-as
LD = /usr/bin/i686-linux-gnu-ld
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = i686-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM)
CXX = /usr/bin/clang++$(LLVM)
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused --target=i686-unknown-linux-gnu
CXX_FLAGS = -std=c++26 -Wall -Wno-unused --target=i686-unknown-linux-gnu
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ)
	$(LD) main.o func.o -o $(TRG) -m elf_i386 --entry=_start
	rm -v $(OBJ)
main.o : main.s
	# $(AS) main.s -o main.o --32
	$(CC) main.s -c $(C_FLAGS) -g
func.o : func.c
	$(CC) func.c -c $(C_FLAGS) $(DEBUG)
format :
	$(FORMAT) func.c -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)
scan :
	$(SCAN) make