#include "CoffeeWithHook.h"
#include <iostream>

void CoffeeWithHook::brew() const { std::cout << "Dripping Coffee through filter" << std::endl; }

void CoffeeWithHook::addCondiments() const { std::cout << "Adding Sugar and Milk" << std::endl; }

bool CoffeeWithHook::customerWantsCondiments() const { return ('y' == getUserInput()) ? true : false; }

char CoffeeWithHook::getUserInput() const
{
    char value;
    std::cout << "Would you like milk and sugar with your coffee (y/n)? " << std::endl;
    std::cin >> value;
    return value;
}