###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
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
$(TRG) : $(OBJ) threadpool.o
	$(CXX) $(OBJ) threadpool.o -o $(TRG) $(CLANGXX_LINK_FLAGS) $(LIBS)
	rm -v $(OBJ)
	rm -v threadpool.o
$(OBJ) : $(SRC)
	$(CXX) $(SRC) -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
threadpool.o : threadpool.cc threadpool.h
	$(CXX) threadpool.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) main.cc -style=file -i
	$(FORMAT) threadpool.cc -style=file -i
	$(FORMAT) threadpool.h -style=file -i
clean :
	rm -v $(TRG)
check :
	valgrind --tool=memcheck --leak-check=full --error-limit=no ./$(TRG)