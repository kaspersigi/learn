###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning\ Leetcode
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
	cd 01.两数之和 && make
	cd 02.两数相加 && make
	cd 03.无重复字符的最长子串 && make
	cd 04.寻找两个正序数组的中位数 && make
	cd 05.最长回文子串 && make
	cd 06.Z字形变换 && make
	cd 07.整数反转 && make
	cd 08.字符串转换整数\(atoi\) && make

format :
	cd 00.template && make format
	cd 01.两数之和 && make format
	cd 02.两数相加 && make format
	cd 03.无重复字符的最长子串 && make format
	cd 04.寻找两个正序数组的中位数 && make format
	cd 05.最长回文子串 && make format
	cd 06.Z字形变换 && make format
	cd 07.整数反转 && make format
	cd 08.字符串转换整数\(atoi\) && make format

clean :
	cd 00.template && make clean
	cd 01.两数之和 && make clean
	cd 02.两数相加 && make clean
	cd 03.无重复字符的最长子串 && make clean
	cd 04.寻找两个正序数组的中位数 && make clean
	cd 05.最长回文子串 && make clean
	cd 06.Z字形变换 && make clean
	cd 07.整数反转 && make clean
	cd 08.字符串转换整数\(atoi\) && make clean