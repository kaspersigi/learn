###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning\ C++
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
all : template macro regex constructor deconstructor interface interface_template smart_pointer const function_template class_template threadpool
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
smart_pointer :
	$(MAKE) -C 07.smart_pointer
const :
	$(MAKE) -C 08.const
function_template :
	$(MAKE) -C 09.function_template
class_template :
	$(MAKE) -C 10.class_template
threadpool :
	$(MAKE) -C 11.threadpool
android_c++ :
	$(MAKE) -C 12.android_c++

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.macro format
	$(MAKE) -C 02.regex format
	$(MAKE) -C 03.constructor format
	$(MAKE) -C 04.deconstructor format
	$(MAKE) -C 05.interface format
	$(MAKE) -C 06.interface_template format
	$(MAKE) -C 07.smart_pointer format
	$(MAKE) -C 08.const format
	$(MAKE) -C 09.function_template format
	$(MAKE) -C 10.class_template format
	$(MAKE) -C 11.threadpool format
	# $(MAKE) -C 12.android_c++ format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.macro clean
	$(MAKE) -C 02.regex clean
	$(MAKE) -C 03.constructor clean
	$(MAKE) -C 04.deconstructor clean
	$(MAKE) -C 05.interface clean
	$(MAKE) -C 06.interface_template clean
	$(MAKE) -C 07.smart_pointer clean
	$(MAKE) -C 08.const clean
	$(MAKE) -C 09.function_template clean
	$(MAKE) -C 10.class_template clean
	$(MAKE) -C 11.threadpool clean
	# $(MAKE) -C 12.android_c++ clean