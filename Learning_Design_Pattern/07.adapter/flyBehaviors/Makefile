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
TIDY = /usr/bin/clang-tidy$(LLVM)
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
all : FlyNoWay.o FlyRocketPowered.o FlyWithWings.o
FlyNoWay.o : FlyNoWay.cc FlyNoWay.h
	$(CXX) FlyNoWay.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
FlyRocketPowered.o : FlyRocketPowered.cc FlyRocketPowered.h
	$(CXX) FlyRocketPowered.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
FlyWithWings.o : FlyWithWings.cc FlyWithWings.h
	$(CXX) FlyWithWings.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) flyBehaviors.h -style=file -i
	$(FORMAT) FlyNoWay.cc -style=file -i
	$(FORMAT) FlyNoWay.h -style=file -i
	$(FORMAT) FlyRocketPowered.cc -style=file -i
	$(FORMAT) FlyRocketPowered.h -style=file -i
	$(FORMAT) FlyWithWings.cc -style=file -i
	$(FORMAT) FlyWithWings.h -style=file -i
clean :
	rm -v FlyNoWay.o FlyRocketPowered.o FlyWithWings.o
scan :
	$(SCAN) make
tidy :
	$(TIDY) FlyNoWay.cc $(TIDY_FLAGS)
	$(TIDY) FlyRocketPowered.cc $(TIDY_FLAGS)
	$(TIDY) FlyWithWings.cc $(TIDY_FLAGS)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)