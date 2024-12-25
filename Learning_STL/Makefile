###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning_STL
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template array vector deque list forward_list set multiset map multimap unordered_set unordered_multiset unordered_map unordered_multimap stack queue priority_queue fill fill_n count count_if find find_if copy copy_n copy_if remove_if transform bind lambda function_object minmax_element equal thread condition_variable async promise
template :
	$(MAKE) -C 00.template
array :
	$(MAKE) -C 01.array
vector :
	$(MAKE) -C 02.vector
deque :
	$(MAKE) -C 03.deque
list :
	$(MAKE) -C 04.list
forward_list :
	$(MAKE) -C 05.forward_list
set :
	$(MAKE) -C 06.set
multiset :
	$(MAKE) -C 07.multiset
map :
	$(MAKE) -C 08.map
multimap :
	$(MAKE) -C 09.multimap
unordered_set :
	$(MAKE) -C 10.unordered_set
unordered_multiset :
	$(MAKE) -C 11.unordered_multiset
unordered_map :
	$(MAKE) -C 12.unordered_map
unordered_multimap :
	$(MAKE) -C 13.unordered_multimap
stack :
	$(MAKE) -C 14.stack
queue :
	$(MAKE) -C 15.queue
priority_queue :
	$(MAKE) -C 16.priority_queue
fill :
	$(MAKE) -C 17.fill
fill_n :
	$(MAKE) -C 18.fill_n
count :
	$(MAKE) -C 19.count
count_if :
	$(MAKE) -C 20.count_if
find :
	$(MAKE) -C 21.find
find_if :
	$(MAKE) -C 22.find_if
copy :
	$(MAKE) -C 23.copy
copy_n :
	$(MAKE) -C 24.copy_n
copy_if :
	$(MAKE) -C 25.copy_if
remove_if :
	$(MAKE) -C 26.remove_if
transform :
	$(MAKE) -C 27.transform
bind :
	$(MAKE) -C 28.bind
lambda :
	$(MAKE) -C 29.lambda
function_object :
	$(MAKE) -C 30.function_object
minmax_element :
	$(MAKE) -C 31.minmax_element
equal :
	$(MAKE) -C 32.equal
thread :
	$(MAKE) -C 33.thread
condition_variable :
	$(MAKE) -C 34.condition_variable
async :
	$(MAKE) -C 35.async
promise :
	$(MAKE) -C 36.promise

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.array format
	$(MAKE) -C 02.vector format
	$(MAKE) -C 03.deque format
	$(MAKE) -C 04.list format
	$(MAKE) -C 05.forward_list format
	$(MAKE) -C 06.set format
	$(MAKE) -C 07.multiset format
	$(MAKE) -C 08.map format
	$(MAKE) -C 09.multimap format
	$(MAKE) -C 10.unordered_set format
	$(MAKE) -C 11.unordered_multiset format
	$(MAKE) -C 12.unordered_map format
	$(MAKE) -C 13.unordered_multimap format
	$(MAKE) -C 14.stack format
	$(MAKE) -C 15.queue format
	$(MAKE) -C 16.priority_queue format
	$(MAKE) -C 17.fill format
	$(MAKE) -C 18.fill_n format
	$(MAKE) -C 19.count format
	$(MAKE) -C 20.count_if format
	$(MAKE) -C 21.find format
	$(MAKE) -C 22.find_if format
	$(MAKE) -C 23.copy format
	$(MAKE) -C 24.copy_n format
	$(MAKE) -C 25.copy_if format
	$(MAKE) -C 26.remove_if format
	$(MAKE) -C 27.transform format
	$(MAKE) -C 28.bind format
	$(MAKE) -C 29.lambda format
	$(MAKE) -C 30.function_object format
	$(MAKE) -C 31.minmax_element format
	$(MAKE) -C 32.equal format
	$(MAKE) -C 33.thread format
	$(MAKE) -C 34.condition_variable format
	$(MAKE) -C 35.async format
	$(MAKE) -C 36.promise format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.array clean
	$(MAKE) -C 02.vector clean
	$(MAKE) -C 03.deque clean
	$(MAKE) -C 04.list clean
	$(MAKE) -C 05.forward_list clean
	$(MAKE) -C 06.set clean
	$(MAKE) -C 07.multiset clean
	$(MAKE) -C 08.map clean
	$(MAKE) -C 09.multimap clean
	$(MAKE) -C 10.unordered_set clean
	$(MAKE) -C 11.unordered_multiset clean
	$(MAKE) -C 12.unordered_map clean
	$(MAKE) -C 13.unordered_multimap clean
	$(MAKE) -C 14.stack clean
	$(MAKE) -C 15.queue clean
	$(MAKE) -C 16.priority_queue clean
	$(MAKE) -C 17.fill clean
	$(MAKE) -C 18.fill_n clean
	$(MAKE) -C 19.count clean
	$(MAKE) -C 20.count_if clean
	$(MAKE) -C 21.find clean
	$(MAKE) -C 22.find_if clean
	$(MAKE) -C 23.copy clean
	$(MAKE) -C 24.copy_n clean
	$(MAKE) -C 25.copy_if clean
	$(MAKE) -C 26.remove_if clean
	$(MAKE) -C 27.transform clean
	$(MAKE) -C 28.bind clean
	$(MAKE) -C 29.lambda clean
	$(MAKE) -C 30.function_object clean
	$(MAKE) -C 31.minmax_element clean
	$(MAKE) -C 32.equal clean
	$(MAKE) -C 33.thread clean
	$(MAKE) -C 34.condition_variable clean
	$(MAKE) -C 35.async clean
	$(MAKE) -C 36.promise clean