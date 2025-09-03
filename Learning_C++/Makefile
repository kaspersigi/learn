###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning_C++
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
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

.PHONY : all
all : template macro regex constructor deconstructor interface interface_template shared_ptr weak_ptr const function_template class_template threadpool iterator class_export class_thread class_async class_promise class_pthread async_callback print_format print path filesystem ifstream ofstream boost_regex static_local_variable singleton ftrace halrequest framecapture
template :
	$(MAKE) -C 00.template
macro :
	$(MAKE) -C 01.macro
regex :
	$(MAKE) -C 02.regex
constructor :
	$(MAKE) -C 03.constructor
deconstructor :
	$(MAKE) -C 04.deconstructor
interface :
	$(MAKE) -C 05.interface
interface_template :
	$(MAKE) -C 06.interface_template
shared_ptr :
	$(MAKE) -C 07.shared_ptr
weak_ptr :
	$(MAKE) -C 08.weak_ptr
const :
	$(MAKE) -C 09.const
function_template :
	$(MAKE) -C 10.function_template
class_template :
	$(MAKE) -C 11.class_template
threadpool :
	$(MAKE) -C 12.threadpool
iterator :
	$(MAKE) -C 13.iterator
class_export :
	$(MAKE) -C 14.class_export
class_thread :
	$(MAKE) -C 15.class_thread
class_async :
	$(MAKE) -C 16.class_async
class_promise :
	$(MAKE) -C 17.class_promise
class_pthread :
	$(MAKE) -C 18.class_pthread
async_callback :
	$(MAKE) -C 19.async_callback
print_format :
	$(MAKE) -C 20.format
print :
	$(MAKE) -C 21.print
path :
	$(MAKE) -C 22.path
filesystem :
	$(MAKE) -C 23.filesystem
ifstream :
	$(MAKE) -C 24.ifstream
ofstream :
	$(MAKE) -C 25.ofstream
boost_regex :
	$(MAKE) -C 26.boost_regex
static_local_variable :
	$(MAKE) -C 27.static_local_variable
singleton :
	$(MAKE) -C 28.singleton
ftrace :
	$(MAKE) -C 29.ftrace
halrequest :
	$(MAKE) -C 30.halrequest
framecapture :
	$(MAKE) -C 31.framecapture

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.macro format
	$(MAKE) -C 02.regex format
	$(MAKE) -C 03.constructor format
	$(MAKE) -C 04.deconstructor format
	$(MAKE) -C 05.interface format
	$(MAKE) -C 06.interface_template format
	$(MAKE) -C 07.shared_ptr format
	$(MAKE) -C 08.weak_ptr format
	$(MAKE) -C 09.const format
	$(MAKE) -C 10.function_template format
	$(MAKE) -C 11.class_template format
	$(MAKE) -C 12.threadpool format
	$(MAKE) -C 13.iterator format
	$(MAKE) -C 14.class_export format
	$(MAKE) -C 15.class_thread format
	$(MAKE) -C 16.class_async format
	$(MAKE) -C 17.class_promise format
	$(MAKE) -C 18.class_pthread format
	$(MAKE) -C 19.async_callback format
	$(MAKE) -C 20.format format
	$(MAKE) -C 21.print format
	$(MAKE) -C 22.path format
	$(MAKE) -C 23.filesystem format
	$(MAKE) -C 24.ifstream format
	$(MAKE) -C 25.ofstream format
	$(MAKE) -C 26.boost_regex format
	$(MAKE) -C 27.static_local_variable format
	$(MAKE) -C 28.singleton format
	$(MAKE) -C 29.ftrace format
	$(MAKE) -C 30.halrequest format
	$(MAKE) -C 31.framecapture format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.macro clean
	$(MAKE) -C 02.regex clean
	$(MAKE) -C 03.constructor clean
	$(MAKE) -C 04.deconstructor clean
	$(MAKE) -C 05.interface clean
	$(MAKE) -C 06.interface_template clean
	$(MAKE) -C 07.shared_ptr clean
	$(MAKE) -C 08.weak_ptr clean
	$(MAKE) -C 09.const clean
	$(MAKE) -C 10.function_template clean
	$(MAKE) -C 11.class_template clean
	$(MAKE) -C 12.threadpool clean
	$(MAKE) -C 13.iterator clean
	$(MAKE) -C 14.class_export clean
	$(MAKE) -C 15.class_thread clean
	$(MAKE) -C 16.class_async clean
	$(MAKE) -C 17.class_promise clean
	$(MAKE) -C 18.class_pthread clean
	$(MAKE) -C 19.async_callback clean
	$(MAKE) -C 20.format clean
	$(MAKE) -C 21.print clean
	$(MAKE) -C 22.path clean
	$(MAKE) -C 23.filesystem clean
	$(MAKE) -C 24.ifstream clean
	$(MAKE) -C 25.ofstream clean
	$(MAKE) -C 26.boost_regex clean
	$(MAKE) -C 27.static_local_variable clean
	$(MAKE) -C 28.singleton clean
	$(MAKE) -C 29.ftrace clean
	$(MAKE) -C 30.halrequest clean
	$(MAKE) -C 31.framecapture clean