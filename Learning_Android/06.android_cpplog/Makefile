###########################################
#Makefile for my Android C++ programs
###########################################

TRG = cpplog
OBJ = cpplog.o
SRC = cpplog.cc

NDK = ~/linux/android-ndk-r27c
TOOLCHAIN = $(NDK)/toolchains/llvm/prebuilt/linux-x86_64
TARGET = aarch64-linux-android
API = 35
CC = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang
CXX = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang++
AR = $(TOOLCHAIN)/bin/llvm-ar
RANLIB = $(TOOLCHAIN)/bin/llvm-ranlib

LLVM = -18
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
# adb push ~/linux/android-ndk-r27c/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/aarch64-linux-android/libc++_shared.so /data/local/tmp/
LIBS = -llog -L. -lc++_shared -Wl,-rpath=.
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS) $(LIBS) $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) $(SRC) -style=file -i
clean :
	rm -v $(TRG)