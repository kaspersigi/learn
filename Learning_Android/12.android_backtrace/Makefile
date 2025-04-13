###########################################
#Makefile for my Android C programs
###########################################

TRG = backtrace
OBJ = backtrace.o
SRC = backtrace.c
NDK = $(HOME)/linux/android-ndk-r27c
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
CC = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang
CXX = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang++
AR = $(TOOLCHAIN)/bin/llvm-ar
LLVM = -20
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -llog
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = -lllvmlibc
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) $(LIBS) $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG)
format :
	$(FORMAT) $(SRC) -style=file -i
clean :
	rm -v $(TRG)
addr2line :
	$(NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin/llvm-addr2line -Cie $(TRG) 0x3e84