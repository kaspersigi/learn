###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
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
all : template array vector deque list forward_list set multiset map multimap unordered_set unordered_multiset unordered_map unordered_multimap stack queue priority_queue fill fill_n count count_if find find_if for_each transform copy copy_if remove_if accumulate sort stable_sort binary_search generate replace unique minmax_element partition rotate shuffle merge set_union partial_sort nth_element adjacent_find search bind lambda function_object equal thread condition_variable async promise
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
for_each :
	$(MAKE) -C 23.for_each
transform :
	$(MAKE) -C 24.transform
copy :
	$(MAKE) -C 25.copy
copy_if :
	$(MAKE) -C 26.copy_if
remove_if :
	$(MAKE) -C 27.remove_if
accumulate :
	$(MAKE) -C 28.accumulate
sort :
	$(MAKE) -C 29.sort
stable_sort :
	$(MAKE) -C 30.stable_sort
binary_search :
	$(MAKE) -C 31.binary_search
generate :
	$(MAKE) -C 32.generate
replace :
	$(MAKE) -C 33.replace
unique :
	$(MAKE) -C 34.unique
minmax_element :
	$(MAKE) -C 35.minmax_element
partition :
	$(MAKE) -C 36.partition
rotate :
	$(MAKE) -C 37.rotate
shuffle:
	$(MAKE) -C 38.shuffle
merge :
	$(MAKE) -C 39.merge
set_union :
	$(MAKE) -C 40.set_union
partial_sort :
	$(MAKE) -C 41.partial_sort
nth_element :
	$(MAKE) -C 42.nth_element
adjacent_find:
	$(MAKE) -C 43.adjacent_find
search :
	$(MAKE) -C 44.search
bind :
	$(MAKE) -C 45.bind
lambda :
	$(MAKE) -C 46.lambda
function_object :
	$(MAKE) -C 47.function_object
equal :
	$(MAKE) -C 48.equal
thread :
	$(MAKE) -C 49.thread
condition_variable :
	$(MAKE) -C 50.condition_variable
async :
	$(MAKE) -C 51.async
promise :
	$(MAKE) -C 52.promise

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
	$(MAKE) -C 23.for_each format
	$(MAKE) -C 24.transform format
	$(MAKE) -C 25.copy format
	$(MAKE) -C 26.copy_if format
	$(MAKE) -C 27.remove_if format
	$(MAKE) -C 28.accumulate format
	$(MAKE) -C 29.sort format
	$(MAKE) -C 30.stable_sort format
	$(MAKE) -C 31.binary_search format
	$(MAKE) -C 32.generate format
	$(MAKE) -C 33.replace format
	$(MAKE) -C 34.unique format
	$(MAKE) -C 35.minmax_element format
	$(MAKE) -C 36.partition format
	$(MAKE) -C 37.rotate format
	$(MAKE) -C 38.shuffle format
	$(MAKE) -C 39.merge format
	$(MAKE) -C 40.set_union format
	$(MAKE) -C 41.partial_sort format
	$(MAKE) -C 42.nth_element format
	$(MAKE) -C 43.adjacent_find format
	$(MAKE) -C 44.search format
	$(MAKE) -C 45.bind format
	$(MAKE) -C 46.lambda format
	$(MAKE) -C 47.function_object format
	$(MAKE) -C 48.equal format
	$(MAKE) -C 49.thread format
	$(MAKE) -C 50.condition_variable format
	$(MAKE) -C 51.async format
	$(MAKE) -C 52.promise format

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
	$(MAKE) -C 23.for_each clean
	$(MAKE) -C 24.transform clean
	$(MAKE) -C 25.copy clean
	$(MAKE) -C 26.copy_if clean
	$(MAKE) -C 27.remove_if clean
	$(MAKE) -C 28.accumulate clean
	$(MAKE) -C 29.sort clean
	$(MAKE) -C 30.stable_sort clean
	$(MAKE) -C 31.binary_search clean
	$(MAKE) -C 32.generate clean
	$(MAKE) -C 33.replace clean
	$(MAKE) -C 34.unique clean
	$(MAKE) -C 35.minmax_element clean
	$(MAKE) -C 36.partition clean
	$(MAKE) -C 37.rotate clean
	$(MAKE) -C 38.shuffle clean
	$(MAKE) -C 39.merge clean
	$(MAKE) -C 40.set_union clean
	$(MAKE) -C 41.partial_sort clean
	$(MAKE) -C 42.nth_element clean
	$(MAKE) -C 43.adjacent_find clean
	$(MAKE) -C 44.search clean
	$(MAKE) -C 45.bind clean
	$(MAKE) -C 46.lambda clean
	$(MAKE) -C 47.function_object clean
	$(MAKE) -C 48.equal clean
	$(MAKE) -C 49.thread clean
	$(MAKE) -C 50.condition_variable clean
	$(MAKE) -C 51.async clean
	$(MAKE) -C 52.promise clean