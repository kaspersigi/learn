###########################################
#Makefile for my Android C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c

NDK = ~/linux/android-ndk-r27c
TOOLCHAIN = $(NDK)/toolchains/llvm/prebuilt/linux-x86_64
TARGET = aarch64-linux-android
API = 35
CC = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang
CXX = $(TOOLCHAIN)/bin/$(TARGET)$(API)-clang++
AR = $(TOOLCHAIN)/bin/llvm-ar
RANLIB = $(TOOLCHAIN)/bin/llvm-ranlib

LLVM = -19
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -llog -L./lib -lOpenCL
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -static -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) $(LIBS) $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG) -I./inc -DCL_TARGET_OPENCL_VERSION=300
format :
	$(FORMAT) inc/CL/cl.h -style=file -i
	$(FORMAT) inc/CL/cl.h -style=file -i
	$(FORMAT) inc/CL/cl_d3d10.h -style=file -i
	$(FORMAT) inc/CL/cl_d3d11.h -style=file -i
	$(FORMAT) inc/CL/cl_dx9_media_sharing.h -style=file -i
	$(FORMAT) inc/CL/cl_dx9_media_sharing_intel.h -style=file -i
	$(FORMAT) inc/CL/cl_egl.h -style=file -i
	$(FORMAT) inc/CL/cl_ext.h -style=file -i
	$(FORMAT) inc/CL/cl_ext_intel.h -style=file -i
	$(FORMAT) inc/CL/cl_function_types.h -style=file -i
	$(FORMAT) inc/CL/cl_gl.h -style=file -i
	$(FORMAT) inc/CL/cl_gl_ext.h -style=file -i
	$(FORMAT) inc/CL/cl_half.h -style=file -i
	$(FORMAT) inc/CL/cl_icd.h -style=file -i
	$(FORMAT) inc/CL/cl_layer.h -style=file -i
	$(FORMAT) inc/CL/cl_platform.h -style=file -i
	$(FORMAT) inc/CL/cl_va_api_media_sharing_intel.h -style=file -i
	$(FORMAT) inc/CL/cl_version.h -style=file -i
	$(FORMAT) inc/CL/opencl.h -style=file -i
	$(FORMAT) $(SRC) -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)