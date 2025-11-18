###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /mnt/develop/linux/learn/Learning_Socket
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
TIDY = /usr/bin/clang-tidy$(LLVM) -quiet
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++
TIDY_FLAGS = -- --target=$(ARCH) $(C_FLAGS) $(DEBUG)

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

scan :
	$(MAKE) -C 00.template scan
	$(MAKE) -C 01.hton scan
	$(MAKE) -C 02.inet_pton scan
	$(MAKE) -C 03.socket scan
	$(MAKE) -C 04.listen scan
	$(MAKE) -C 05.accept scan
	$(MAKE) -C 06.connect scan
	$(MAKE) -C 07.recv scan
	$(MAKE) -C 08.send scan
	$(MAKE) -C 09.server scan
	$(MAKE) -C 10.client scan
	$(MAKE) -C 11.threadpool scan
	$(MAKE) -C 12.select scan
	$(MAKE) -C 13.multithread scan
	$(MAKE) -C 14.poll scan
	$(MAKE) -C 15.epoll scan
	$(MAKE) -C 16.level_triggered scan
	$(MAKE) -C 17.edge_triggered scan
	$(MAKE) -C 18.edge_triggered_nonblock scan
	$(MAKE) -C 19.multithread_epoll scan
	$(MAKE) -C 20.threadpool_epoll scan
	$(MAKE) -C 21.myhttpd scan

tidy :
	$(MAKE) -C 00.template tidy
	$(MAKE) -C 01.hton tidy
	$(MAKE) -C 02.inet_pton tidy
	$(MAKE) -C 03.socket tidy
	$(MAKE) -C 04.listen tidy
	$(MAKE) -C 05.accept tidy
	$(MAKE) -C 06.connect tidy
	$(MAKE) -C 07.recv tidy
	$(MAKE) -C 08.send tidy
	$(MAKE) -C 09.server tidy
	$(MAKE) -C 10.client tidy
	$(MAKE) -C 11.threadpool tidy
	$(MAKE) -C 12.select tidy
	$(MAKE) -C 13.multithread tidy
	$(MAKE) -C 14.poll tidy
	$(MAKE) -C 15.epoll tidy
	$(MAKE) -C 16.level_triggered tidy
	$(MAKE) -C 17.edge_triggered tidy
	$(MAKE) -C 18.edge_triggered_nonblock tidy
	$(MAKE) -C 19.multithread_epoll tidy
	$(MAKE) -C 20.threadpool_epoll tidy
	$(MAKE) -C 21.myhttpd tidy