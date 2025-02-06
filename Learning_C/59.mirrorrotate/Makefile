###########################################
#Makefile for my C programs
###########################################

TRG = main
OBJ = main.o
SRC = main.c
LLVM = -19
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
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	$(CC) $(OBJ) -o $(TRG) -L ./lib -lexif -Wl,-rpath=./lib $(DEBUG)
	rm -v $(OBJ)
$(OBJ) : $(SRC)
	$(CC) $(SRC) -c $(C_FLAGS) $(DEBUG) -I ./inc
format :
	$(FORMAT) inc/libexif/exif-byte-order.h -style=file -i
	$(FORMAT) inc/libexif/exif-content.h -style=file -i
	$(FORMAT) inc/libexif/exif-data-type.h -style=file -i
	$(FORMAT) inc/libexif/exif-data.h -style=file -i
	$(FORMAT) inc/libexif/exif-entry.h -style=file -i
	$(FORMAT) inc/libexif/exif-format.h -style=file -i
	$(FORMAT) inc/libexif/exif-gps-ifd.h -style=file -i
	$(FORMAT) inc/libexif/exif-ifd.h -style=file -i
	$(FORMAT) inc/libexif/exif-loader.h -style=file -i
	$(FORMAT) inc/libexif/exif-log.h -style=file -i
	$(FORMAT) inc/libexif/exif-mem.h -style=file -i
	$(FORMAT) inc/libexif/exif-mnote-data-priv.h -style=file -i
	$(FORMAT) inc/libexif/exif-mnote-data.h -style=file -i
	$(FORMAT) inc/libexif/exif-system.h -style=file -i
	$(FORMAT) inc/libexif/exif-tag.h -style=file -i
	$(FORMAT) inc/libexif/exif-utils.h -style=file -i
	$(FORMAT) inc/libexif/exif.h -style=file -i
	$(FORMAT) main.c -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --error-limit=no ./$(TRG)