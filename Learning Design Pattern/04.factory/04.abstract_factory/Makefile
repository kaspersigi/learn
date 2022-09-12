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
RELEASE = -static -O3
LINK_FLAGS = -no-pie
LIBS = -lpthread
CLANGXX_FLAGS = -stdlib=libc++
CLANGXX_LINK_FLAGS = -lc++ -nostdlib++

.PHONY : all
all : Pizzaaf
Pizzaaf : Pizzaaf.o interface.o cheese.o clams.o dough.o pepperoni.o sauce.o veggies.o factories.o pizzas.o stores.o
	$(CXX) Pizzaaf.o interface/Pizza.o interface/PizzaStore.o cheese/MozzarellaCheese.o cheese/ParmesanCheese.o cheese/ReggianoCheese.o clams/FreshClams.o clams/FrozenClams.o dough/ThickCrustDough.o dough/ThinCrustDough.o pepperoni/SlicedPepperoni.o sauce/MarinaraSauce.o sauce/PlumTomatoSauce.o veggies/BlackOlives.o veggies/Eggplant.o veggies/Garlic.o veggies/Mushroom.o veggies/Onion.o veggies/RedPepper.o veggies/Spinach.o factories/ChicagoPizzaIngredientFactory.o factories/NYPizzaIngredientFactory.o pizzas/CheesePizza.o pizzas/ClamPizza.o pizzas/PepperoniPizza.o pizzas/VeggiePizza.o stores/ChicagoPizzaStore.o stores/NYPizzaStore.o -o Pizzaaf $(CLANGXX_LINK_FLAGS)
	rm -v Pizzaaf.o
	$(MAKE) -C interface clean
	$(MAKE) -C cheese clean
	$(MAKE) -C clams clean
	$(MAKE) -C dough clean
	$(MAKE) -C pepperoni clean
	$(MAKE) -C sauce clean
	$(MAKE) -C veggies clean
	$(MAKE) -C factories clean
	$(MAKE) -C pizzas clean
	$(MAKE) -C stores clean
Pizzaaf.o : Pizzaaf.cc Pizzaaf.h
	$(CXX) Pizzaaf.cc -c $(CXX_FLAGS) $(CLANGXX_FLAGS) $(DEBUG)
interface.o :
	$(MAKE) -C interface
cheese.o :
	$(MAKE) -C cheese
clams.o :
	$(MAKE) -C clams
dough.o :
	$(MAKE) -C dough
pepperoni.o :
	$(MAKE) -C pepperoni
sauce.o :
	$(MAKE) -C sauce
veggies.o :
	$(MAKE) -C veggies
factories.o :
	$(MAKE) -C factories
pizzas.o :
	$(MAKE) -C pizzas
stores.o :
	$(MAKE) -C stores
format :
	$(FORMAT) Pizzaaf.cc -style=file -i
	$(FORMAT) Pizzaaf.h -style=file -i
	$(MAKE) -C interface format
	$(MAKE) -C cheese format
	$(MAKE) -C clams format
	$(MAKE) -C dough format
	$(MAKE) -C pepperoni format
	$(MAKE) -C sauce format
	$(MAKE) -C veggies format
	$(MAKE) -C factories format
	$(MAKE) -C pizzas format
	$(MAKE) -C stores format
clean :
	rm -v Pizzaaf