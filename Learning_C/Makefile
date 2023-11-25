###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_C
ARCH = $(shell llvm-config --host-target)
CC = /usr/bin/clang --target=$(ARCH)
CXX = /usr/bin/clang++ --target=$(ARCH)
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template macro static_library dynamic_library dlsym open write read fopen line_buffer all_buffer mkdir opendir readdir fork vfork pipe mkfifo kill raise alarm pause signal shmget ftok shmat shmctl msgget msgsnd msgrcv semget semop one_producer_one_consumer_sem multi_producer_multi_consumer_sem pthread_create pthread_exit pthread_join pthread_detach pthread_cancel pthread_kill sigaction pthread_cleanup pthread_mutex pthread_rwlock pthread_cond one_producer_one_consumer_cond multi_producer_multi_consumer_cond perror union threadpool asm asm_call_c inline_asm syscall mmap polymorphism complex_macro
template :
	$(MAKE) -C 00.template
macro :
	$(MAKE) -C 01.macro
static_library :
	$(MAKE) -C 02.static_library
dynamic_library :
	$(MAKE) -C 03.dynamic_library
dlsym :
	$(MAKE) -C 04.dlsym
open :
	$(MAKE) -C 05.open
write :
	$(MAKE) -C 06.write
read :
	$(MAKE) -C 07.read
fopen :
	$(MAKE) -C 08.fopen
line_buffer :
	$(MAKE) -C 09.line_buffer
all_buffer :
	$(MAKE) -C 10.all_buffer
mkdir :
	$(MAKE) -C 11.mkdir
opendir :
	$(MAKE) -C 12.opendir
readdir :
	$(MAKE) -C 13.readdir
fork :
	$(MAKE) -C 14.fork
vfork :
	$(MAKE) -C 15.vfork
pipe :
	$(MAKE) -C 16.pipe
mkfifo :
	$(MAKE) -C 17.mkfifo
kill :
	$(MAKE) -C 18.kill
raise :
	$(MAKE) -C 19.raise
alarm :
	$(MAKE) -C 20.alarm
pause :
	$(MAKE) -C 21.pause
signal :
	$(MAKE) -C 22.signal
shmget :
	$(MAKE) -C 23.shmget
ftok :
	$(MAKE) -C 24.ftok
shmat :
	$(MAKE) -C 25.shmat
shmctl :
	$(MAKE) -C 26.shmctl
msgget :
	$(MAKE) -C 27.msgget
msgsnd :
	$(MAKE) -C 28.msgsnd
msgrcv :
	$(MAKE) -C 29.msgrcv
semget :
	$(MAKE) -C 30.semget
semop :
	$(MAKE) -C 31.semop
one_producer_one_consumer_sem :
	$(MAKE) -C 32.one_producer_one_consumer_sem
multi_producer_multi_consumer_sem :
	$(MAKE) -C 33.multi_producer_multi_consumer_sem
pthread_create :
	$(MAKE) -C 34.pthread_create
pthread_exit :
	$(MAKE) -C 35.pthread_exit
pthread_join :
	$(MAKE) -C 36.pthread_join
pthread_detach :
	$(MAKE) -C 37.pthread_detach
pthread_cancel :
	$(MAKE) -C 38.pthread_cancel
pthread_kill :
	$(MAKE) -C 39.pthread_kill
sigaction :
	$(MAKE) -C 40.sigaction
pthread_cleanup :
	$(MAKE) -C 41.pthread_cleanup
pthread_mutex :
	$(MAKE) -C 42.pthread_mutex
pthread_rwlock :
	$(MAKE) -C 43.pthread_rwlock
pthread_cond :
	$(MAKE) -C 44.pthread_cond
one_producer_one_consumer_cond :
	$(MAKE) -C 45.one_producer_one_consumer_cond
multi_producer_multi_consumer_cond :
	$(MAKE) -C 46.multi_producer_multi_consumer_cond
perror :
	$(MAKE) -C 47.perror
union :
	$(MAKE) -C 48.union
threadpool :
	$(MAKE) -C 49.threadpool
asm :
	$(MAKE) -C 50.asm
asm_call_c :
	$(MAKE) -C 51.asm_call_c
inline_asm :
	$(MAKE) -C 52.inline_asm
syscall :
	$(MAKE) -C 53.syscall
mmap :
	$(MAKE) -C 54.mmap
polymorphism :
	$(MAKE) -C 55.polymorphism
complex_macro :
	$(MAKE) -C 56.complex_macro

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
	# $(MAKE) -C 50.asm format
	$(MAKE) -C 51.asm_call_c format
	$(MAKE) -C 52.inline_asm format
	$(MAKE) -C 53.syscall format
	$(MAKE) -C 54.mmap format
	$(MAKE) -C 55.polymorphism format
	$(MAKE) -C 56.complex_macro format

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
	$(MAKE) -C 50.asm clean
	$(MAKE) -C 51.asm_call_c clean
	$(MAKE) -C 52.inline_asm clean
	$(MAKE) -C 53.syscall clean
	$(MAKE) -C 54.mmap clean
	$(MAKE) -C 55.polymorphism clean
	$(MAKE) -C 56.complex_macro clean