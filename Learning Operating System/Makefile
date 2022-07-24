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
	cd 00.template && make
	cd 01.gas && make
	cd 02.floppy && make
	cd 03.userapp && make
	cd 04.interrupt && make
	cd 05.bios && make
	cd 06.protected && make
	cd 07.sort && make
	cd 08.kernel && make
	cd 09.boot && make
	cd 10.api && make
	cd 11.tcb && make
	cd 12.cpl && make
	cd 13.collaborative_task_switch && make
	cd 14.preemptive_task_switch && make

clean :
	cd 00.template && make clean
	cd 01.gas && make clean
	cd 02.floppy && make clean
	cd 03.userapp && make clean
	cd 04.interrupt && make clean
	cd 05.bios && make clean
	cd 06.protected && make clean
	cd 07.sort && make clean
	cd 08.kernel && make clean
	cd 09.boot && make clean
	cd 10.api && make clean
	cd 11.tcb && make clean
	cd 12.cpl && make clean
	cd 13.collaborative_task_switch && make clean
	cd 14.preemptive_task_switch && make clean