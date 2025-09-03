###########################################
#Makefile for my C programs
###########################################

TRG = clinfo
OBJ = clinfo.o
SRC = clinfo.c
LLVM = -21
CONFIG = llvm-config$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format$(LLVM)
C_FLAGS = -std=c23 -Wall -Wno-unused
CXX_FLAGS = -std=c++26 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -flto -O3
LIBS = -L../lib/$(shell uname -m) -lOpenCL -Wl,-rpath=../lib/$(shell uname -m)
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -nostdlib++ -lc++

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) $(LIBS)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG) -I./inc -I../inc
format :
	$(FORMAT) ../inc/CL/cl.h -style=file -i
	$(FORMAT) ../inc/CL/cl_d3d10.h -style=file -i
	$(FORMAT) ../inc/CL/cl_d3d11.h -style=file -i
	$(FORMAT) ../inc/CL/cl_dx9_media_sharing.h -style=file -i
	$(FORMAT) ../inc/CL/cl_dx9_media_sharing_intel.h -style=file -i
	$(FORMAT) ../inc/CL/cl_egl.h -style=file -i
	$(FORMAT) ../inc/CL/cl_ext.h -style=file -i
	$(FORMAT) ../inc/CL/cl_ext_intel.h -style=file -i
	$(FORMAT) ../inc/CL/cl_function_types.h -style=file -i
	$(FORMAT) ../inc/CL/cl_gl.h -style=file -i
	$(FORMAT) ../inc/CL/cl_gl_ext.h -style=file -i
	$(FORMAT) ../inc/CL/cl_half.h -style=file -i
	$(FORMAT) ../inc/CL/cl_icd.h -style=file -i
	$(FORMAT) ../inc/CL/cl_layer.h -style=file -i
	$(FORMAT) ../inc/CL/cl_platform.h -style=file -i
	$(FORMAT) ../inc/CL/cl_va_api_media_sharing_intel.h -style=file -i
	$(FORMAT) ../inc/CL/cl_version.h -style=file -i
	$(FORMAT) ../inc/CL/opencl.h -style=file -i
	$(FORMAT) inc/ctx_prop.h -style=file -i
	$(FORMAT) inc/error.h -style=file -i
	$(FORMAT) inc/ext.h -style=file -i
	$(FORMAT) inc/fmtmacros.h -style=file -i
	$(FORMAT) inc/info_loc.h -style=file -i
	$(FORMAT) inc/info_ret.h -style=file -i
	$(FORMAT) inc/memory.h -style=file -i
	$(FORMAT) inc/ms_support.h -style=file -i
	$(FORMAT) inc/opt_out.h -style=file -i
	$(FORMAT) inc/strbuf.h -style=file -i
	$(FORMAT) $(SRC) -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)