###########################################
#Makefile for my Android C programs
###########################################

TRG = main
OBJ = main.o ftrace.o
SRC = main.c ftrace.c
NDK = /mnt/develop/android-ndk-r27d
ARCH = $(shell uname -m)
PLATFORM = darwin
ifeq ($(ARCH), x86_64)
	PLATFORM = linux
else ifeq ($(ARCH), aarch64)
	PLATFORM = windows
endif
TOOLCHAIN = $(NDK)/toolchains/llvm/prebuilt/$(PLATFORM)-x86_64
TARGET = aarch64-linux-android
API = 35
LLVM = -21
CC = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang
CXX = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang++
SCAN = scan-build$(LLVM) --use-cc=$(CC) --use-c++=$(CXX)
TIDY = /usr/bin/clang-tidy$(LLVM) -quiet
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused --sysroot=$(TOOLCHAIN)/sysroot --target=$(TARGET)
CXX_FLAGS = -std=c++26 -Wall -Wno-unused --sysroot=$(TOOLCHAIN)/sysroot --target=$(TARGET)
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -L $(TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(API)/ -landroid -llog
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -static-libstdc++
TIDY_FLAGS = -- $(C_FLAGS) $(DEBUG)

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG)
	rm -v $(OBJ)
main.o : main.c
	$(CC) main.c -c $(C_FLAGS) $(DEBUG)
ftrace.o : ftrace.c
	$(CC) ftrace.c -c $(C_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.c -style=file -i
	$(FORMAT) ftrace.c -style=file -i
	$(FORMAT) ftrace.h -style=file -i
clean :
	rm -v $(TRG)
scan :
	$(SCAN) make
tidy :
	$(TIDY) main.c $(TIDY_FLAGS)
	$(TIDY) ftrace.c $(TIDY_FLAGS)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)