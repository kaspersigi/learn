###########################################
#Makefile for my Android C programs
###########################################

TRG = setschedparam
OBJ = setschedparam.o ftrace.o
SRC = setschedparam.c ftrace.c
NDK = $(HOME)/linux/android-ndk-r27c
ARCH = $(shell uname -m)
PLATFORM = linux
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
	$(CC) $(OBJ) -o $(TRG) $(LIBS) $(RELEASE)
	rm -v $(OBJ)
setschedparam.o : setschedparam.c
	$(CC) setschedparam.c -c $(C_FLAGS) $(CLANG_FLAGS) $(DEBUG)
ftrace.o : ftrace.c
	$(CC) ftrace.c -c $(C_FLAGS) $(CLANG_FLAGS) $(DEBUG)
format :
	$(FORMAT) $(SRC) -style=file -i
	$(FORMAT) ftrace.c -style=file -i
	$(FORMAT) ftrace.h -style=file -i
clean :
	rm -v $(TRG)