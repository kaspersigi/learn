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
	cd 0.template && make
	cd 1.hton && make
	cd 2.inet_pton && make
	cd 3.socket && make
	cd 4.listen && make
	cd 5.accept && make
	cd 6.connect && make
	cd 7.recv && make
	cd 8.send && make
	cd 9.server && make
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
	cd 0.template && make format
	cd 1.hton && make format
	cd 2.inet_pton && make format
	cd 3.socket && make format
	cd 4.listen && make format
	cd 5.accept && make format
	cd 6.connect && make format
	cd 7.recv && make format
	cd 8.send && make format
	cd 9.server && make format
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
	cd 0.template && make clean
	cd 1.hton && make clean
	cd 2.inet_pton && make clean
	cd 3.socket && make clean
	cd 4.listen && make clean
	cd 5.accept && make clean
	cd 6.connect && make clean
	cd 7.recv && make clean
	cd 8.send && make clean
	cd 9.server && make clean
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