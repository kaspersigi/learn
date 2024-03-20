###########################################
#Makefile for my C++ programs
###########################################

TRG = main
OBJ = main.o
SRC = main.cc
LLVM = 17
CONFIG = llvm-config-$(LLVM)
ARCH = $(shell $(CONFIG) --host-target)
CC = /usr/bin/clang-$(LLVM) --target=$(ARCH)
CXX = /usr/bin/clang++-$(LLVM) --target=$(ARCH)
FORMAT = /usr/bin/clang-format-$(LLVM)
C_FLAGS = -std=c18 -Wall -Wno-unused
CXX_FLAGS = -std=c++23 -Wall -Wno-unused
DEBUG = -g -O0
RELEASE = -static -Oz
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : ChicagoStyleCheesePizza.o ChicagoStyleClamPizza.o ChicagoStylePepperoniPizza.o ChicagoStyleVeggiePizza.o NYStyleCheesePizza.o NYStyleClamPizza.o NYStylePepperoniPizza.o NYStyleVeggiePizza.o
ChicagoStyleCheesePizza.o : ChicagoStyleCheesePizza.cc ChicagoStyleCheesePizza.h
	$(CXX) ChicagoStyleCheesePizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ChicagoStyleClamPizza.o : ChicagoStyleClamPizza.cc ChicagoStyleClamPizza.h
	$(CXX) ChicagoStyleClamPizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ChicagoStylePepperoniPizza.o : ChicagoStylePepperoniPizza.cc ChicagoStylePepperoniPizza.h
	$(CXX) ChicagoStylePepperoniPizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
ChicagoStyleVeggiePizza.o : ChicagoStyleVeggiePizza.cc ChicagoStyleVeggiePizza.h
	$(CXX) ChicagoStyleVeggiePizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NYStyleCheesePizza.o : NYStyleCheesePizza.cc NYStyleCheesePizza.h
	$(CXX) NYStyleCheesePizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NYStyleClamPizza.o : NYStyleClamPizza.cc NYStyleClamPizza.h
	$(CXX) NYStyleClamPizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NYStylePepperoniPizza.o : NYStylePepperoniPizza.cc NYStylePepperoniPizza.h
	$(CXX) NYStylePepperoniPizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
NYStyleVeggiePizza.o : NYStyleVeggiePizza.cc NYStyleVeggiePizza.h
	$(CXX) NYStyleVeggiePizza.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
format :
	$(FORMAT) ChicagoStylePizzas.h -style=file -i
	$(FORMAT) NYStylePizzas.h -style=file -i
	$(FORMAT) ChicagoStyleCheesePizza.cc -style=file -i
	$(FORMAT) ChicagoStyleCheesePizza.h -style=file -i
	$(FORMAT) ChicagoStyleClamPizza.cc -style=file -i
	$(FORMAT) ChicagoStyleClamPizza.h -style=file -i
	$(FORMAT) ChicagoStylePepperoniPizza.cc -style=file -i
	$(FORMAT) ChicagoStylePepperoniPizza.h -style=file -i
	$(FORMAT) ChicagoStyleVeggiePizza.cc -style=file -i
	$(FORMAT) ChicagoStyleVeggiePizza.h -style=file -i
	$(FORMAT) NYStyleCheesePizza.cc -style=file -i
	$(FORMAT) NYStyleCheesePizza.h -style=file -i
	$(FORMAT) NYStyleClamPizza.cc -style=file -i
	$(FORMAT) NYStyleClamPizza.h -style=file -i
	$(FORMAT) NYStylePepperoniPizza.cc -style=file -i
	$(FORMAT) NYStylePepperoniPizza.h -style=file -i
	$(FORMAT) NYStyleVeggiePizza.cc -style=file -i
	$(FORMAT) NYStyleVeggiePizza.h -style=file -i
clean :
	rm -v ChicagoStyleCheesePizza.o ChicagoStyleClamPizza.o ChicagoStylePepperoniPizza.o ChicagoStyleVeggiePizza.o NYStyleCheesePizza.o NYStyleClamPizza.o NYStylePepperoniPizza.o NYStyleVeggiePizza.o