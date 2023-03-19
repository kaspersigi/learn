#include "Coffee.h"
#include <iostream>

void Coffee::brew() const { std::cout << "Dripping Coffee through filter" << std::endl; }

void Coffee::addCondiments() const { std::cout << "Adding Sugar and Milk" << std::endl; }