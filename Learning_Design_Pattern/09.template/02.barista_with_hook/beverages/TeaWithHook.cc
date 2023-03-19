#include "TeaWithHook.h"
#include <iostream>

void TeaWithHook::brew() const { std::cout << "Steeping the tea" << std::endl; }

void TeaWithHook::addCondiments() const { std::cout << "Adding Lemon" << std::endl; }

bool TeaWithHook::customerWantsCondiments() const { return ('y' == getUserInput()) ? true : false; }

char TeaWithHook::getUserInput() const
{
    char value;
    std::cout << "Would you like lemon with your tea (y/n)? " << std::endl;
    std::cin >> value;
    return value;
}