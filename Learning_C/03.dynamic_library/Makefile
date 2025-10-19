###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
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
LIBS = -ldl -L. -lfunc -Wl,-rpath=.
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++
TIDY_FLAGS = -- --target=$(ARCH) $(C_FLAGS) $(DEBUG)

.PHONY : all
$(TRG) : main.o libfunc.so
	$(CC) main.o -o $(TRG) $(LIBS)
	rm -v main.o
main.o : main.c
	$(CC) main.c -c $(C_FLAGS) $(DEBUG)
libfunc.so : func.o
	$(CC) func.o -o libfunc.so -shared $(DEBUG)
	rm -v func.o
func.o : func.c func.h
	$(CC) func.c -c $(C_FLAGS) $(DEBUG) -fPIC
format :
	$(FORMAT) main.c -style=file -i
	$(FORMAT) func.h -style=file -i
	$(FORMAT) func.c -style=file -i
clean :
	rm -v $(TRG) libfunc.so
scan :
	$(SCAN) make
tidy :
	$(TIDY) main.c $(TIDY_FLAGS)
	$(TIDY) func.c $(TIDY_FLAGS)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)