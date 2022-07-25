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
	$(MAKE) -C 01.gas
	$(MAKE) -C 02.floppy
	$(MAKE) -C 03.userapp
	$(MAKE) -C 04.interrupt
	$(MAKE) -C 05.bios
	$(MAKE) -C 06.protected
	$(MAKE) -C 07.sort
	$(MAKE) -C 08.kernel
	$(MAKE) -C 09.boot
	$(MAKE) -C 10.api
	$(MAKE) -C 11.tcb
	$(MAKE) -C 12.cpl
	$(MAKE) -C 13.collaborative_task_switch
	$(MAKE) -C 14.preemptive_task_switch

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.gas clean
	$(MAKE) -C 02.floppy clean
	$(MAKE) -C 03.userapp clean
	$(MAKE) -C 04.interrupt clean
	$(MAKE) -C 05.bios clean
	$(MAKE) -C 06.protected clean
	$(MAKE) -C 07.sort clean
	$(MAKE) -C 08.kernel clean
	$(MAKE) -C 09.boot clean
	$(MAKE) -C 10.api clean
	$(MAKE) -C 11.tcb clean
	$(MAKE) -C 12.cpl clean
	$(MAKE) -C 13.collaborative_task_switch clean
	$(MAKE) -C 14.preemptive_task_switch clean