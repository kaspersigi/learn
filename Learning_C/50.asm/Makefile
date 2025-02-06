###########################################
#Makefile for my assembler programs
###########################################

TRG = main
OBJ = main.o
SRC = main.s
AS = /usr/bin/i686-linux-gnu-as
LD = /usr/bin/i686-linux-gnu-ld
LLVM = -19
CONFIG = llvm-config$(LLVM)
ARCH = i386-unknown-linux-gnu
CC = /usr/bin/clang$(LLVM) --target=i386-unknown-linux-gnu
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	$(LD) $(OBJ) -o $(TRG) -m elf_i386 --entry=_start
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	# $(AS) $(SRC) -o $(OBJ) --32
	$(CC) $(SRC) -c
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)