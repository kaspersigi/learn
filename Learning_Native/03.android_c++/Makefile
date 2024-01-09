###########################################
#Makefile for my Android C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc

NDK = ~/linux/android-ndk-r26
TOOLCHAIN = $(NDK)/toolchains/llvm/prebuilt/linux-x86_64
TARGET = aarch64-linux-android
API = 34
CC = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang
CXX = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang++
AR = $(TOOLCHAIN)/bin/llvm-ar
RANLIB = $(TOOLCHAIN)/bin/llvm-ranlib

FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c2x -Wall -Wno-unused
CXX_FLAGS = -std=c++2b -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	# vivo自带libc++_shared.so，不需要-static，htc、huawei都需要
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS) -static
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.cc -style=file -i
clean :
	rm -v $(TRG)