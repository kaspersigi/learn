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
	$(MAKE) -C 00.template
	$(MAKE) -C 01.两数之和
	$(MAKE) -C 02.两数相加
	$(MAKE) -C 03.无重复字符的最长子串
	$(MAKE) -C 04.寻找两个正序数组的中位数
	$(MAKE) -C 05.最长回文子串
	$(MAKE) -C 06.Z字形变换
	$(MAKE) -C 07.整数反转
	$(MAKE) -C 08.字符串转换整数\(atoi\)

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.两数之和 format
	$(MAKE) -C 02.两数相加 format
	$(MAKE) -C 03.无重复字符的最长子串 format
	$(MAKE) -C 04.寻找两个正序数组的中位数 format
	$(MAKE) -C 05.最长回文子串 format
	$(MAKE) -C 06.Z字形变换 format
	$(MAKE) -C 07.整数反转 format
	$(MAKE) -C 08.字符串转换整数\(atoi\) format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.两数之和 clean
	$(MAKE) -C 02.两数相加 clean
	$(MAKE) -C 03.无重复字符的最长子串 clean
	$(MAKE) -C 04.寻找两个正序数组的中位数 clean
	$(MAKE) -C 05.最长回文子串 clean
	$(MAKE) -C 06.Z字形变换 clean
	$(MAKE) -C 07.整数反转 clean
	$(MAKE) -C 08.字符串转换整数\(atoi\) clean