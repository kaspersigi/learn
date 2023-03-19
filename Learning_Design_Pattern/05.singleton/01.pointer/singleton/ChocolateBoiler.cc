#include "ChocolateBoiler.h"
#include <iostream>

ChocolateBoiler* ChocolateBoiler::_uniqueInstance = nullptr;

ChocolateBoiler::~ChocolateBoiler()
{
    std::cout << "Destroy instance of Chocolate Boiler" << std::endl;
    // 只是因为没有指针等资源需要释放，此处应该有资源回收动作
    _uniqueInstance = nullptr;
}

ChocolateBoiler* ChocolateBoiler::getInstance()
{
    if (nullptr == _uniqueInstance) {
        std::cout << "Creating unique instance of Chocolate Boiler" << std::endl;
        _uniqueInstance = new ChocolateBoiler();
    }
    std::cout << "Returning instance of Chocolate Boiler" << std::endl;
    return _uniqueInstance;
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