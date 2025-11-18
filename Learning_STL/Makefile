###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /mnt/develop/linux/learn/Learning_STL
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
TIDY_FLAGS = -- --target=$(ARCH) $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)

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

scan :
	$(MAKE) -C 00.template scan
	$(MAKE) -C 01.array scan
	$(MAKE) -C 02.vector scan
	$(MAKE) -C 03.deque scan
	$(MAKE) -C 04.list scan
	$(MAKE) -C 05.forward_list scan
	$(MAKE) -C 06.set scan
	$(MAKE) -C 07.multiset scan
	$(MAKE) -C 08.map scan
	$(MAKE) -C 09.multimap scan
	$(MAKE) -C 10.unordered_set scan
	$(MAKE) -C 11.unordered_multiset scan
	$(MAKE) -C 12.unordered_map scan
	$(MAKE) -C 13.unordered_multimap scan
	$(MAKE) -C 14.stack scan
	$(MAKE) -C 15.queue scan
	$(MAKE) -C 16.priority_queue scan
	$(MAKE) -C 17.fill scan
	$(MAKE) -C 18.fill_n scan
	$(MAKE) -C 19.count scan
	$(MAKE) -C 20.count_if scan
	$(MAKE) -C 21.find scan
	$(MAKE) -C 22.find_if scan
	$(MAKE) -C 23.for_each scan
	$(MAKE) -C 24.transform scan
	$(MAKE) -C 25.copy scan
	$(MAKE) -C 26.copy_if scan
	$(MAKE) -C 27.remove_if scan
	$(MAKE) -C 28.accumulate scan
	$(MAKE) -C 29.sort scan
	$(MAKE) -C 30.stable_sort scan
	$(MAKE) -C 31.binary_search scan
	$(MAKE) -C 32.generate scan
	$(MAKE) -C 33.replace scan
	$(MAKE) -C 34.unique scan
	$(MAKE) -C 35.minmax_element scan
	$(MAKE) -C 36.partition scan
	$(MAKE) -C 37.rotate scan
	$(MAKE) -C 38.shuffle scan
	$(MAKE) -C 39.merge scan
	$(MAKE) -C 40.set_union scan
	$(MAKE) -C 41.partial_sort scan
	$(MAKE) -C 42.nth_element scan
	$(MAKE) -C 43.adjacent_find scan
	$(MAKE) -C 44.search scan
	$(MAKE) -C 45.bind scan
	$(MAKE) -C 46.lambda scan
	$(MAKE) -C 47.function_object scan
	$(MAKE) -C 48.equal scan
	$(MAKE) -C 49.thread scan
	$(MAKE) -C 50.condition_variable scan
	$(MAKE) -C 51.async scan
	$(MAKE) -C 52.promise scan

tidy :
	$(MAKE) -C 00.template tidy
	$(MAKE) -C 01.array tidy
	$(MAKE) -C 02.vector tidy
	$(MAKE) -C 03.deque tidy
	$(MAKE) -C 04.list tidy
	$(MAKE) -C 05.forward_list tidy
	$(MAKE) -C 06.set tidy
	$(MAKE) -C 07.multiset tidy
	$(MAKE) -C 08.map tidy
	$(MAKE) -C 09.multimap tidy
	$(MAKE) -C 10.unordered_set tidy
	$(MAKE) -C 11.unordered_multiset tidy
	$(MAKE) -C 12.unordered_map tidy
	$(MAKE) -C 13.unordered_multimap tidy
	$(MAKE) -C 14.stack tidy
	$(MAKE) -C 15.queue tidy
	$(MAKE) -C 16.priority_queue tidy
	$(MAKE) -C 17.fill tidy
	$(MAKE) -C 18.fill_n tidy
	$(MAKE) -C 19.count tidy
	$(MAKE) -C 20.count_if tidy
	$(MAKE) -C 21.find tidy
	$(MAKE) -C 22.find_if tidy
	$(MAKE) -C 23.for_each tidy
	$(MAKE) -C 24.transform tidy
	$(MAKE) -C 25.copy tidy
	$(MAKE) -C 26.copy_if tidy
	$(MAKE) -C 27.remove_if tidy
	$(MAKE) -C 28.accumulate tidy
	$(MAKE) -C 29.sort tidy
	$(MAKE) -C 30.stable_sort tidy
	$(MAKE) -C 31.binary_search tidy
	$(MAKE) -C 32.generate tidy
	$(MAKE) -C 33.replace tidy
	$(MAKE) -C 34.unique tidy
	$(MAKE) -C 35.minmax_element tidy
	$(MAKE) -C 36.partition tidy
	$(MAKE) -C 37.rotate tidy
	$(MAKE) -C 38.shuffle tidy
	$(MAKE) -C 39.merge tidy
	$(MAKE) -C 40.set_union tidy
	$(MAKE) -C 41.partial_sort tidy
	$(MAKE) -C 42.nth_element tidy
	$(MAKE) -C 43.adjacent_find tidy
	$(MAKE) -C 44.search tidy
	$(MAKE) -C 45.bind tidy
	$(MAKE) -C 46.lambda tidy
	$(MAKE) -C 47.function_object tidy
	$(MAKE) -C 48.equal tidy
	$(MAKE) -C 49.thread tidy
	$(MAKE) -C 50.condition_variable tidy
	$(MAKE) -C 51.async tidy
	$(MAKE) -C 52.promise tidy