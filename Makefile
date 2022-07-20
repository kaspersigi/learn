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
all :
	cd C\ Threadpool && make
	cd C++\ Threadpool && make
	cd Learning\ C && make
	cd Learning\ C++ && make
	cd Learning\ Design\ Pattern && make
	cd Learning\ Leetcode && make
	cd Learning\ Operating\ System && make
	cd Learning\ Rust && make
	cd Learning\ Socket && make
	cd Learning\ STL && make

format :
	cd C\ Threadpool && make format
	cd C++\ Threadpool && make format
	cd Learning\ C && make format
	cd Learning\ C++ && make format
	cd Learning\ Design\ Pattern && make format
	cd Learning\ Leetcode && make format
	# cd Learning\ Operating\ System && make format
	cd Learning\ Rust && make format
	cd Learning\ Socket && make format
	cd Learning\ STL && make format

clean :
	cd C\ Threadpool && make clean
	cd C++\ Threadpool && make clean
	cd Learning\ C && make clean
	cd Learning\ C++ && make clean
	cd Learning\ Design\ Pattern && make clean
	cd Learning\ Leetcode && make clean
	cd Learning\ Operating\ System && make clean
	cd Learning\ Rust && make clean
	cd Learning\ Socket && make clean
	cd Learning\ STL && make clean

bak :
	git archive --format=tar.gz --output ../learn.tar.gz master