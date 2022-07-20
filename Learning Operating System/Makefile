###########################################
#Makefile for my assembler programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning\ Operating\ System
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all :
	cd 0.template && make
	cd 1.gas && make
	cd 2.floppy && make
	cd 3.userapp && make
	cd 4.interrupt && make
	cd 5.bios && make
	cd 6.protected && make
	cd 7.sort && make
	cd 8.kernel && make
	cd 9.boot && make
	cd 10.api && make
	cd 11.tcb && make
	cd 12.cpl && make
	cd 13.schedule && make

clean :
	cd 0.template && make clean
	cd 1.gas && make clean
	cd 2.floppy && make clean
	cd 3.userapp && make clean
	cd 4.interrupt && make clean
	cd 5.bios && make clean
	cd 6.protected && make clean
	cd 7.sort && make clean
	cd 8.kernel && make clean
	cd 9.boot && make clean
	cd 10.api && make clean
	cd 11.tcb && make clean
	cd 12.cpl && make clean
	cd 13.schedule && make clean
