###########################################
#Makefile for my programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn
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
all : c c++ design_pattern leetcode operating_system rust socket stl
c :
	$(MAKE) -C Learning\ C
c++ :
	$(MAKE) -C Learning\ C++
design_pattern :
	$(MAKE) -C Learning\ Design\ Pattern
leetcode :
	$(MAKE) -C Learning\ Leetcode
operating_system :
	$(MAKE) -C Learning\ Operating\ System
rust :
	$(MAKE) -C Learning\ Rust
socket :
	$(MAKE) -C Learning\ Socket
stl :
	$(MAKE) -C Learning\ STL

format :
	$(MAKE) -C Learning\ C format
	$(MAKE) -C Learning\ C++ format
	$(MAKE) -C Learning\ Design\ Pattern format
	$(MAKE) -C Learning\ Leetcode format
	# $(MAKE) -C Learning\ Operating\ System format
	$(MAKE) -C Learning\ Rust format
	$(MAKE) -C Learning\ Socket format
	$(MAKE) -C Learning\ STL format

clean :
	$(MAKE) -C Learning\ C clean
	$(MAKE) -C Learning\ C++ clean
	$(MAKE) -C Learning\ Design\ Pattern clean
	$(MAKE) -C Learning\ Leetcode clean
	$(MAKE) -C Learning\ Operating\ System clean
	$(MAKE) -C Learning\ Rust clean
	$(MAKE) -C Learning\ Socket clean
	$(MAKE) -C Learning\ STL clean

bak :
	git archive --format=tar.gz --output ../learn.tar.gz master