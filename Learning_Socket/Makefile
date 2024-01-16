###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Socket
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template hton inet_pton socket listen accept connect recv send server client threadpool select multithread poll epoll level_triggered edge_triggered edge_triggered_nonblock multithread_epoll threadpool_epoll myhttpd
template :
	$(MAKE) -C 00.template
hton :
	$(MAKE) -C 01.hton
inet_pton :
	$(MAKE) -C 02.inet_pton
socket :
	$(MAKE) -C 03.socket
listen :
	$(MAKE) -C 04.listen
accept :
	$(MAKE) -C 05.accept
connect :
	$(MAKE) -C 06.connect
recv :
	$(MAKE) -C 07.recv
send :
	$(MAKE) -C 08.send
server :
	$(MAKE) -C 09.server
client :
	$(MAKE) -C 10.client
threadpool :
	$(MAKE) -C 11.threadpool
select :
	$(MAKE) -C 12.select
multithread :
	$(MAKE) -C 13.multithread
poll :
	$(MAKE) -C 14.poll
epoll :
	$(MAKE) -C 15.epoll
level_triggered :
	$(MAKE) -C 16.level_triggered
edge_triggered :
	$(MAKE) -C 17.edge_triggered
edge_triggered_nonblock :
	$(MAKE) -C 18.edge_triggered_nonblock
multithread_epoll :
	$(MAKE) -C 19.multithread_epoll
threadpool_epoll :
	$(MAKE) -C 20.threadpool_epoll
myhttpd :
	$(MAKE) -C 21.myhttpd

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.hton format
	$(MAKE) -C 02.inet_pton format
	$(MAKE) -C 03.socket format
	$(MAKE) -C 04.listen format
	$(MAKE) -C 05.accept format
	$(MAKE) -C 06.connect format
	$(MAKE) -C 07.recv format
	$(MAKE) -C 08.send format
	$(MAKE) -C 09.server format
	$(MAKE) -C 10.client format
	$(MAKE) -C 11.threadpool format
	$(MAKE) -C 12.select format
	$(MAKE) -C 13.multithread format
	$(MAKE) -C 14.poll format
	$(MAKE) -C 15.epoll format
	$(MAKE) -C 16.level_triggered format
	$(MAKE) -C 17.edge_triggered format
	$(MAKE) -C 18.edge_triggered_nonblock format
	$(MAKE) -C 19.multithread_epoll format
	$(MAKE) -C 20.threadpool_epoll format
	$(MAKE) -C 21.myhttpd format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.hton clean
	$(MAKE) -C 02.inet_pton clean
	$(MAKE) -C 03.socket clean
	$(MAKE) -C 04.listen clean
	$(MAKE) -C 05.accept clean
	$(MAKE) -C 06.connect clean
	$(MAKE) -C 07.recv clean
	$(MAKE) -C 08.send clean
	$(MAKE) -C 09.server clean
	$(MAKE) -C 10.client clean
	$(MAKE) -C 11.threadpool clean
	$(MAKE) -C 12.select clean
	$(MAKE) -C 13.multithread clean
	$(MAKE) -C 14.poll clean
	$(MAKE) -C 15.epoll clean
	$(MAKE) -C 16.level_triggered clean
	$(MAKE) -C 17.edge_triggered clean
	$(MAKE) -C 18.edge_triggered_nonblock clean
	$(MAKE) -C 19.multithread_epoll clean
	$(MAKE) -C 20.threadpool_epoll clean
	$(MAKE) -C 21.myhttpd clean