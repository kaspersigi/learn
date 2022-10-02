###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning\ C
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
all : template driver android_c android_c++ rust
template :
	$(MAKE) -C 00.template
driver :
	$(MAKE) -C 01.driver
android_c :
	$(MAKE) -C 02.android_c
android_c++ :
	$(MAKE) -C 03.android_c++
rust :
	$(MAKE) -C 04.rust

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.driver format
	$(MAKE) -C 02.android_c format
	$(MAKE) -C 03.android_c++ format
	# $(MAKE) -C 04.rust format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.driver clean
	$(MAKE) -C 02.android_c clean
	$(MAKE) -C 03.android_c++ clean
	$(MAKE) -C 04.rust clean