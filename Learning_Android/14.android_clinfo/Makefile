###########################################
#Makefile for my Android C programs
###########################################

TRG = clinfo
OBJ = clinfo.o
SRC = clinfo.c
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
LIBS = -L $(TOOLCHAIN)/sysroot/usr/lib/$(TARGET)/$(API)/ -landroid -llog -L./lib -lOpenCL
LLVMLIBC = /usr/lib/llvm$(LLVM)/lib/
CLANG_FLAGS = -nostdlib
CLANG_LINK_FLAGS = /usr/lib/llvm$(LLVM)/lib/libllvmlibc.a -static
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -static-libstdc++
TIDY_FLAGS = -- $(C_FLAGS) $(DEBUG)

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) $(LIBS)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG) -I./inc
format :
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
scan :
	$(SCAN) make
tidy :
	$(TIDY) $(SRC) $(TIDY_FLAGS) -I./inc
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)