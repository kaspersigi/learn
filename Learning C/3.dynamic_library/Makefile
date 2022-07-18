###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
CC = /usr/bin/clang
CXX = /usr/bin/clang++
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
FORMAT = /usr/bin/clang-format
DEBUG = -g -O0
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ) libfunc.so
	$(CC) $(OBJ) -o $(TRG) -L. -lfunc -Wl,-rpath=.
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG)
libfunc.so : func.o
	$(CC) func.o -o libfunc.so -shared -fPIC
	rm -v func.o
func.o : func.c func.h
	$(CC) func.c -c $(C_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.c -style=file -i
	$(FORMAT) func.c -style=file -i
	$(FORMAT) func.h -style=file -i
clean :
	rm -v $(TRG)
		rm -v libfunc.so