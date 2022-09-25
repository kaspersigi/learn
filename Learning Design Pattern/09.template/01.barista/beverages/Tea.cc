#include "Tea.h"
#include <iostream>

void Tea::brew() const { std::cout << "Steeping the tea" << std::endl; }

void Tea::addCondiments() const { std::cout << "Adding Lemon" << std::endl; }