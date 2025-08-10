###########################################
#Makefile for my Android programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_Android
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
LIBS = -lpthread
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
all : template android_c android_cpp android_ftrace android_atrace android_clog android_cpplog android_setpriority android_nice android_setschedparam android_setscheduler android_native_buf android_backtrace android_detach android_clinfo android_opencl android_dlopen
template :
	$(MAKE) -C 00.template
android_c :
	$(MAKE) -C 01.android_c
android_cpp :
	$(MAKE) -C 02.android_cpp
android_ftrace:
	$(MAKE) -C 03.android_ftrace
android_atrace :
	$(MAKE) -C 04.android_atrace
android_clog :
	$(MAKE) -C 05.android_clog
android_cpplog :
	$(MAKE) -C 06.android_cpplog
android_setpriority :
	$(MAKE) -C 07.android_setpriority
android_nice :
	$(MAKE) -C 08.android_nice
android_setschedparam :
	$(MAKE) -C 09.android_setschedparam
android_setscheduler :
	$(MAKE) -C 10.android_setscheduler
android_native_buf :
	$(MAKE) -C 11.android_native_buf
android_backtrace :
	$(MAKE) -C 12.android_backtrace
android_detach :
	$(MAKE) -C 13.android_detach
android_clinfo :
	$(MAKE) -C 14.android_clinfo
android_opencl :
	$(MAKE) -C 15.android_opencl
android_dlopen :
	$(MAKE) -C 16.android_dlopen

format :
	$(MAKE) -C 00.template format
	$(MAKE) -C 01.android_c format
	$(MAKE) -C 02.android_cpp format
	$(MAKE) -C 03.android_ftrace format
	$(MAKE) -C 04.android_atrace format
	$(MAKE) -C 05.android_clog format
	$(MAKE) -C 06.android_cpplog format
	$(MAKE) -C 07.android_setpriority format
	$(MAKE) -C 08.android_nice format
	$(MAKE) -C 09.android_setschedparam format
	$(MAKE) -C 10.android_setscheduler format
	$(MAKE) -C 11.android_native_buf format
	$(MAKE) -C 12.android_backtrace format
	$(MAKE) -C 13.android_detach format
	$(MAKE) -C 14.android_clinfo format
	$(MAKE) -C 15.android_opencl format
	$(MAKE) -C 16.android_dlopen format

clean :
	$(MAKE) -C 00.template clean
	$(MAKE) -C 01.android_c clean
	$(MAKE) -C 02.android_cpp clean
	$(MAKE) -C 03.android_ftrace clean
	$(MAKE) -C 04.android_atrace clean
	$(MAKE) -C 05.android_clog clean
	$(MAKE) -C 06.android_cpplog clean
	$(MAKE) -C 07.android_setpriority clean
	$(MAKE) -C 08.android_nice clean
	$(MAKE) -C 09.android_setschedparam clean
	$(MAKE) -C 10.android_setscheduler clean
	$(MAKE) -C 11.android_native_buf clean
	$(MAKE) -C 12.android_backtrace clean
	$(MAKE) -C 13.android_detach clean
	$(MAKE) -C 14.android_clinfo clean
	$(MAKE) -C 15.android_opencl clean
	$(MAKE) -C 16.android_dlopen clean