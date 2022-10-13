###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o IObject.o Object.o
SRC = main.cc
CC = /usr/bin/clang
CXX = /usr/bin/clang++
FORMAT = /usr/bin/clang-format
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++20 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
$(TRG) : $(OBJ)
	$(CXX) $(OBJ) -o $(TRG) $(CLANGXX_LINK_FLAGS)
	rm -v $(OBJ)
main.o : main.cc IObject.h
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
IObject.o : IObject.cc IObject.h
	$(CXX) IObject.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
Object.o : Object.cc Object.h
	$(CXX) Object.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.cc -style=file -i
	$(FORMAT) IObject.h -style=file -i
	$(FORMAT) IObject.cc -style=file -i
	$(FORMAT) Object.h -style=file -i
	$(FORMAT) Object.cc -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --error-limit=no ./$(TRG)