#include "ChocolateBoiler.h"
#include <iostream>

ChocolateBoiler& ChocolateBoiler::getInstance()
{
    std::cout << "Returning instance of Chocolate Boiler" << std::endl;
    static ChocolateBoiler instance;
    return instance;
}

bool ChocolateBoiler::isEmpty() const { return _empty; }

bool ChocolateBoiler::isBoiled() const { return _boiled; }

void ChocolateBoiler::fill()
{
    if (isEmpty()) {
        _empty = false;
        _boiled = false;
    }
}

void ChocolateBoiler::drain()
{
    if (!isEmpty() && isBoiled()) {
        _empty = true;
    }
}
void ChocolateBoiler::boil()
{
    if (!isEmpty() && !isBoiled()) {
        _boiled = true;
    }
}