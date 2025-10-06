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
SCAN = scan-build$(LLVM) --use-cc=/usr/bin/clang$(LLVM) --use-c++=/usr/bin/clang++$(LLVM)
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
all : Pizza.o PizzaStore.o
Pizza.o : Pizza.cc Pizza.h
	$(CXX) Pizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
PizzaStore.o : PizzaStore.cc PizzaStore.h
	$(CXX) PizzaStore.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) Pizza.cc -style=file -i
	$(FORMAT) Pizza.h -style=file -i
	$(FORMAT) PizzaStore.cc -style=file -i
	$(FORMAT) PizzaStore.h -style=file -i
	$(FORMAT) Cheese.h -style=file -i
	$(FORMAT) Clams.h -style=file -i
	$(FORMAT) Dough.h -style=file -i
	$(FORMAT) Pepperoni.h -style=file -i
	$(FORMAT) Sauce.h -style=file -i
	$(FORMAT) Veggies.h -style=file -i
	$(FORMAT) PizzaIngredientFactory.h -style=file -i
	$(FORMAT) NonCopyable.h -style=file -i
clean :
	rm -v Pizza.o PizzaStore.o
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)
scan :
	$(SCAN) make