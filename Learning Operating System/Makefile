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
all : 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17
00 :
	$(MAKE) -C 00.template
01 :
	$(MAKE) -C 01.cpuid
02 :
	$(MAKE) -C 02.asm
03 :
	$(MAKE) -C 03.protected
04 :
	$(MAKE) -C 04.kernel
05 :
	$(MAKE) -C 05.userapp
06 :
	$(MAKE) -C 06.interrupt
07 :
	$(MAKE) -C 07.bios
08 :
	$(MAKE) -C 08.protected
09 :
	$(MAKE) -C 09.sort
10 :
	$(MAKE) -C 10.kernel
11 :
	$(MAKE) -C 11.boot
12 :
	$(MAKE) -C 12.api
13 :
	$(MAKE) -C 13.tcb
14 :
	$(MAKE) -C 14.cpl
15 :
	$(MAKE) -C 15.collaborative_task_switch
16 :
	$(MAKE) -C 16.preemptive_task_switch
17 :
	$(MAKE) -C 17.paging

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.cpuid clean
	$(MAKE) -C 02.asm clean
	$(MAKE) -C 03.protected clean
	$(MAKE) -C 04.kernel clean
	$(MAKE) -C 05.userapp clean
	$(MAKE) -C 06.interrupt clean
	$(MAKE) -C 07.bios clean
	$(MAKE) -C 08.protected clean
	$(MAKE) -C 09.sort clean
	$(MAKE) -C 10.kernel clean
	$(MAKE) -C 11.boot clean
	$(MAKE) -C 12.api clean
	$(MAKE) -C 13.tcb clean
	$(MAKE) -C 14.cpl clean
	$(MAKE) -C 15.collaborative_task_switch clean
	$(MAKE) -C 16.preemptive_task_switch clean
	$(MAKE) -C 17.paging clean