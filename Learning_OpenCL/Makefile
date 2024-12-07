###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
VPATH = /home/miku/learn/Learning_C
LLVM = -18
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -L../lib -lOpenCL
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : template
template :
	$(MAKE) -C 00.template

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
	$(MAKE) -C 00.template format

clean :
	$(MAKE) -C 00.template clean