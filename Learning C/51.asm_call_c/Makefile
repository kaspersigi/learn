###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o func.o
SRC = main.c
AS = /usr/bin/as
LD = /usr/bin/ld
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++
ARCH = -m32

.PHONY : all
$(TRG) : $(OBJ)
	$(LD) main.o func.o -o $(TRG) -m elf_i386 --entry=_start
	rm -v $(OBJ)
main.o : main.s
	# $(AS) main.s -o main.o --32
	$(CC) main.s -c -no-integrated-as $(ARCH)
func.o : func.c
	$(CC) func.c -c $(C_FLAGS) $(DEBUG) $(ARCH)
format :
	$(FORMAT) func.c -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)