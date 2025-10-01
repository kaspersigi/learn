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
all : BlackOlives.o Eggplant.o Garlic.o Mushroom.o Onion.o RedPepper.o Spinach.o
BlackOlives.o : BlackOlives.cc BlackOlives.h
	$(CXX) BlackOlives.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Eggplant.o : Eggplant.cc Eggplant.h
	$(CXX) Eggplant.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Garlic.o : Garlic.cc Garlic.h
	$(CXX) Garlic.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Mushroom.o : Mushroom.cc Mushroom.h
	$(CXX) Mushroom.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Onion.o : Onion.cc Onion.h
	$(CXX) Onion.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
RedPepper.o : RedPepper.cc RedPepper.h
	$(CXX) RedPepper.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Spinach.o : Spinach.cc Spinach.h
	$(CXX) Spinach.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) BlackOlives.cc -style=file -i
	$(FORMAT) BlackOlives.h -style=file -i
	$(FORMAT) Eggplant.cc -style=file -i
	$(FORMAT) Eggplant.h -style=file -i
	$(FORMAT) Garlic.cc -style=file -i
	$(FORMAT) Garlic.h -style=file -i
	$(FORMAT) Mushroom.cc -style=file -i
	$(FORMAT) Mushroom.h -style=file -i
	$(FORMAT) Onion.cc -style=file -i
	$(FORMAT) Onion.h -style=file -i
	$(FORMAT) RedPepper.cc -style=file -i
	$(FORMAT) RedPepper.h -style=file -i
	$(FORMAT) Spinach.cc -style=file -i
	$(FORMAT) Spinach.h -style=file -i
clean :
	rm -v BlackOlives.o Eggplant.o Garlic.o Mushroom.o Onion.o RedPepper.o Spinach.o
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)
scan :
	$(SCAN) make