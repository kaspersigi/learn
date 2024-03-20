###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
VPATH = /home/miku/learn/Learning_C++
LLVM = -17
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template binary_search remove_element squares_of_a_sorted_array minimum_size_subarray_sum spiral_matrix_ii remove_linked_list_elements design_linked_list reverse_linked_list swap_nodes_in_pairs remove_nth_node_from_end_of_list intersection_of_two_linked_lists_lcci linked_list_cycle_ii valid_anagram intersection_of_two_arrays happy_number two_sum 4sum_ii ransom_note 3sum
template :
	$(MAKE) -C 00.template
binary_search :
	$(MAKE) -C 01.binary_search
remove_element :
	$(MAKE) -C 02.remove_element
squares_of_a_sorted_array :
	$(MAKE) -C 03.squares_of_a_sorted_array
minimum_size_subarray_sum :
	$(MAKE) -C 04.minimum_size_subarray_sum
spiral_matrix_ii :
	$(MAKE) -C 05.spiral_matrix_ii
remove_linked_list_elements :
	$(MAKE) -C 06.remove_linked_list_elements
design_linked_list :
	$(MAKE) -C 07.design_linked_list
reverse_linked_list :
	$(MAKE) -C 08.reverse_linked_list
swap_nodes_in_pairs :
	$(MAKE) -C 09.swap_nodes_in_pairs
remove_nth_node_from_end_of_list :
	$(MAKE) -C 10.remove_nth_node_from_end_of_list
intersection_of_two_linked_lists_lcci :
	$(MAKE) -C 11.intersection_of_two_linked_lists_lcci
linked_list_cycle_ii :
	$(MAKE) -C 12.linked_list_cycle_ii
valid_anagram :
	$(MAKE) -C 13.valid_anagram
intersection_of_two_arrays :
	$(MAKE) -C 14.intersection_of_two_arrays
happy_number :
	$(MAKE) -C 15.happy_number
two_sum :
	$(MAKE) -C 16.two_sum
4sum_ii :
	$(MAKE) -C 17.4sum_ii
ransom_note :
	$(MAKE) -C 18.ransom_note
3sum :
	$(MAKE) -C 19.3sum

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.binary_search format
	$(MAKE) -C 02.remove_element format
	$(MAKE) -C 03.squares_of_a_sorted_array format
	$(MAKE) -C 04.minimum_size_subarray_sum format
	$(MAKE) -C 05.spiral_matrix_ii format
	$(MAKE) -C 06.remove_linked_list_elements format
	$(MAKE) -C 07.design_linked_list format
	$(MAKE) -C 08.reverse_linked_list format
	$(MAKE) -C 09.swap_nodes_in_pairs format
	$(MAKE) -C 10.remove_nth_node_from_end_of_list format
	$(MAKE) -C 11.intersection_of_two_linked_lists_lcci format
	$(MAKE) -C 12.linked_list_cycle_ii format
	$(MAKE) -C 13.valid_anagram format
	$(MAKE) -C 14.intersection_of_two_arrays format
	$(MAKE) -C 15.happy_number format
	$(MAKE) -C 16.two_sum format
	$(MAKE) -C 17.4sum_ii format
	$(MAKE) -C 18.ransom_note format
	$(MAKE) -C 19.3sum format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.binary_search clean
	$(MAKE) -C 02.remove_element clean
	$(MAKE) -C 03.squares_of_a_sorted_array clean
	$(MAKE) -C 04.minimum_size_subarray_sum clean
	$(MAKE) -C 05.spiral_matrix_ii clean
	$(MAKE) -C 06.remove_linked_list_elements clean
	$(MAKE) -C 07.design_linked_list clean
	$(MAKE) -C 08.reverse_linked_list clean
	$(MAKE) -C 09.swap_nodes_in_pairs clean
	$(MAKE) -C 10.remove_nth_node_from_end_of_list clean
	$(MAKE) -C 11.intersection_of_two_linked_lists_lcci clean
	$(MAKE) -C 12.linked_list_cycle_ii clean
	$(MAKE) -C 13.valid_anagram clean
	$(MAKE) -C 14.intersection_of_two_arrays clean
	$(MAKE) -C 15.happy_number clean
	$(MAKE) -C 16.two_sum clean
	$(MAKE) -C 17.4sum_ii clean
	$(MAKE) -C 18.ransom_note clean
	$(MAKE) -C 19.3sum clean