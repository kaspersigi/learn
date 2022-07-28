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
	$(MAKE) -C 00.template
	$(MAKE) -C 01.cpuid
	$(MAKE) -C 02.asm
	$(MAKE) -C 03.protected
	$(MAKE) -C 04.kernel
	$(MAKE) -C 05.userapp
	$(MAKE) -C 06.interrupt
	$(MAKE) -C 07.bios
	$(MAKE) -C 08.protected
	$(MAKE) -C 09.sort
	$(MAKE) -C 10.kernel
	$(MAKE) -C 11.boot
	$(MAKE) -C 12.api
	$(MAKE) -C 13.tcb
	$(MAKE) -C 14.cpl
	$(MAKE) -C 15.collaborative_task_switch
	$(MAKE) -C 16.preemptive_task_switch

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