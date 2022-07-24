###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning\ Socket
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
	cd 01.hton && make
	cd 02.inet_pton && make
	cd 03.socket && make
	cd 04.listen && make
	cd 05.accept && make
	cd 06.connect && make
	cd 07.recv && make
	cd 08.send && make
	cd 09.server && make
	cd 10.client && make
	cd 11.threadpool && make
	cd 12.select && make
	cd 13.multithread && make
	cd 14.poll && make
	cd 15.epoll && make
	cd 16.level_triggered && make
	cd 17.edge_triggered && make
	cd 18.edge_triggered_nonblock && make
	cd 19.multithread_epoll && make
	cd 20.threadpool_epoll && make
	cd 21.myhttpd && make

format :
	cd 00.template && make format
	cd 01.hton && make format
	cd 02.inet_pton && make format
	cd 03.socket && make format
	cd 04.listen && make format
	cd 05.accept && make format
	cd 06.connect && make format
	cd 07.recv && make format
	cd 08.send && make format
	cd 09.server && make format
	cd 10.client && make format
	cd 11.threadpool && make format
	cd 12.select && make format
	cd 13.multithread && make format
	cd 14.poll && make format
	cd 15.epoll && make format
	cd 16.level_triggered && make format
	cd 17.edge_triggered && make format
	cd 18.edge_triggered_nonblock && make format
	cd 19.multithread_epoll && make format
	cd 20.threadpool_epoll && make format
	cd 21.myhttpd && make format

clean :
	cd 00.template && make clean
	cd 01.hton && make clean
	cd 02.inet_pton && make clean
	cd 03.socket && make clean
	cd 04.listen && make clean
	cd 05.accept && make clean
	cd 06.connect && make clean
	cd 07.recv && make clean
	cd 08.send && make clean
	cd 09.server && make clean
	cd 10.client && make clean
	cd 11.threadpool && make clean
	cd 12.select && make clean
	cd 13.multithread && make clean
	cd 14.poll && make clean
	cd 15.epoll && make clean
	cd 16.level_triggered && make clean
	cd 17.edge_triggered && make clean
	cd 18.edge_triggered_nonblock && make clean
	cd 19.multithread_epoll && make clean
	cd 20.threadpool_epoll && make clean
	cd 21.myhttpd && make clean