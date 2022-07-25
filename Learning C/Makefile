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
all :
	$(MAKE) -C 00.template
	$(MAKE) -C 01.macro
	$(MAKE) -C 02.static_library
	$(MAKE) -C 03.dynamic_library
	$(MAKE) -C 04.dlsym
	$(MAKE) -C 05.open
	$(MAKE) -C 06.write
	$(MAKE) -C 07.read
	$(MAKE) -C 08.fopen
	$(MAKE) -C 09.line_buffer
	$(MAKE) -C 10.all_buffer
	$(MAKE) -C 11.mkdir
	$(MAKE) -C 12.opendir
	$(MAKE) -C 13.readdir
	$(MAKE) -C 14.fork
	$(MAKE) -C 15.vfork
	$(MAKE) -C 16.pipe
	$(MAKE) -C 17.mkfifo
	$(MAKE) -C 18.kill
	$(MAKE) -C 19.raise
	$(MAKE) -C 20.alarm
	$(MAKE) -C 21.pause
	$(MAKE) -C 22.signal
	$(MAKE) -C 23.shmget
	$(MAKE) -C 24.ftok
	$(MAKE) -C 25.shmat
	$(MAKE) -C 26.shmctl
	$(MAKE) -C 27.msgget
	$(MAKE) -C 28.msgsnd
	$(MAKE) -C 29.msgrcv
	$(MAKE) -C 30.semget
	$(MAKE) -C 31.semop
	$(MAKE) -C 32.one_producer_one_consumer_sem
	$(MAKE) -C 33.multi_producer_multi_consumer_sem
	$(MAKE) -C 34.pthread_create
	$(MAKE) -C 35.pthread_exit
	$(MAKE) -C 36.pthread_join
	$(MAKE) -C 37.pthread_detach
	$(MAKE) -C 38.pthread_cancel
	$(MAKE) -C 39.pthread_kill
	$(MAKE) -C 40.sigaction
	$(MAKE) -C 41.pthread_cleanup
	$(MAKE) -C 42.pthread_mutex
	$(MAKE) -C 43.pthread_rwlock
	$(MAKE) -C 44.pthread_cond
	$(MAKE) -C 45.one_producer_one_consumer_cond
	$(MAKE) -C 46.multi_producer_multi_consumer_cond
	$(MAKE) -C 47.perror
	$(MAKE) -C 48.union
	$(MAKE) -C 49.threadpool

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.macro format
	$(MAKE) -C 02.static_library format
	$(MAKE) -C 03.dynamic_library format
	$(MAKE) -C 04.dlsym format
	$(MAKE) -C 05.open format
	$(MAKE) -C 06.write format
	$(MAKE) -C 07.read format
	$(MAKE) -C 08.fopen format
	$(MAKE) -C 09.line_buffer format
	$(MAKE) -C 10.all_buffer format
	$(MAKE) -C 11.mkdir format
	$(MAKE) -C 12.opendir format
	$(MAKE) -C 13.readdir format
	$(MAKE) -C 14.fork format
	$(MAKE) -C 15.vfork format
	$(MAKE) -C 16.pipe format
	$(MAKE) -C 17.mkfifo format
	$(MAKE) -C 18.kill format
	$(MAKE) -C 19.raise format
	$(MAKE) -C 20.alarm format
	$(MAKE) -C 21.pause format
	$(MAKE) -C 22.signal format
	$(MAKE) -C 23.shmget format
	$(MAKE) -C 24.ftok format
	$(MAKE) -C 25.shmat format
	$(MAKE) -C 26.shmctl format
	$(MAKE) -C 27.msgget format
	$(MAKE) -C 28.msgsnd format
	$(MAKE) -C 29.msgrcv format
	$(MAKE) -C 30.semget format
	$(MAKE) -C 31.semop format
	$(MAKE) -C 32.one_producer_one_consumer_sem format
	$(MAKE) -C 33.multi_producer_multi_consumer_sem format
	$(MAKE) -C 34.pthread_create format
	$(MAKE) -C 35.pthread_exit format
	$(MAKE) -C 36.pthread_join format
	$(MAKE) -C 37.pthread_detach format
	$(MAKE) -C 38.pthread_cancel format
	$(MAKE) -C 39.pthread_kill format
	$(MAKE) -C 40.sigaction format
	$(MAKE) -C 41.pthread_cleanup format
	$(MAKE) -C 42.pthread_mutex format
	$(MAKE) -C 43.pthread_rwlock format
	$(MAKE) -C 44.pthread_cond format
	$(MAKE) -C 45.one_producer_one_consumer_cond format
	$(MAKE) -C 46.multi_producer_multi_consumer_cond format
	$(MAKE) -C 47.perror format
	$(MAKE) -C 48.union format
	$(MAKE) -C 49.threadpool format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.macro clean
	$(MAKE) -C 02.static_library clean
	$(MAKE) -C 03.dynamic_library clean
	$(MAKE) -C 04.dlsym clean
	$(MAKE) -C 05.open clean
	$(MAKE) -C 06.write clean
	$(MAKE) -C 07.read clean
	$(MAKE) -C 08.fopen clean
	$(MAKE) -C 09.line_buffer clean
	$(MAKE) -C 10.all_buffer clean
	$(MAKE) -C 11.mkdir clean
	$(MAKE) -C 12.opendir clean
	$(MAKE) -C 13.readdir clean
	$(MAKE) -C 14.fork clean
	$(MAKE) -C 15.vfork clean
	$(MAKE) -C 16.pipe clean
	$(MAKE) -C 17.mkfifo clean
	$(MAKE) -C 18.kill clean
	$(MAKE) -C 19.raise clean
	$(MAKE) -C 20.alarm clean
	$(MAKE) -C 21.pause clean
	$(MAKE) -C 22.signal clean
	$(MAKE) -C 23.shmget clean
	$(MAKE) -C 24.ftok clean
	$(MAKE) -C 25.shmat clean
	$(MAKE) -C 26.shmctl clean
	$(MAKE) -C 27.msgget clean
	$(MAKE) -C 28.msgsnd clean
	$(MAKE) -C 29.msgrcv clean
	$(MAKE) -C 30.semget clean
	$(MAKE) -C 31.semop clean
	$(MAKE) -C 32.one_producer_one_consumer_sem clean
	$(MAKE) -C 33.multi_producer_multi_consumer_sem clean
	$(MAKE) -C 34.pthread_create clean
	$(MAKE) -C 35.pthread_exit clean
	$(MAKE) -C 36.pthread_join clean
	$(MAKE) -C 37.pthread_detach clean
	$(MAKE) -C 38.pthread_cancel clean
	$(MAKE) -C 39.pthread_kill clean
	$(MAKE) -C 40.sigaction clean
	$(MAKE) -C 41.pthread_cleanup clean
	$(MAKE) -C 42.pthread_mutex clean
	$(MAKE) -C 43.pthread_rwlock clean
	$(MAKE) -C 44.pthread_cond clean
	$(MAKE) -C 45.one_producer_one_consumer_cond clean
	$(MAKE) -C 46.multi_producer_multi_consumer_cond clean
	$(MAKE) -C 47.perror clean
	$(MAKE) -C 48.union clean
	$(MAKE) -C 49.threadpool clean