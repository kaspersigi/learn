###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning_C++
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template macro regex constructor deconstructor interface interface_template shared_ptr weak_ptr const function_template class_template threadpool iterator function_pointer class_export class_thread async_callback
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
function_pointer :
	$(MAKE) -C 14.function_pointer
class_export :
	$(MAKE) -C 15.class_export
class_thread :
	$(MAKE) -C 16.class_thread
async_callback :
	$(MAKE) -C 17.async_callback

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
	$(MAKE) -C 14.function_pointer format
	$(MAKE) -C 15.class_export format
	$(MAKE) -C 16.class_thread format
	$(MAKE) -C 17.async_callback format

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
	$(MAKE) -C 14.function_pointer clean
	$(MAKE) -C 15.class_export clean
	$(MAKE) -C 16.class_thread clean
	$(MAKE) -C 17.async_callback clean