#include "Milk.h"

extern "C" {
#include "assert.h"
}

Milk::Milk(const Beverage* beverage)
    : _beverage(beverage)
{
    assert(beverage);
}

std::string Milk::getDescription() const
{
    return _beverage->getDescription() + ", Milk";
}

double Milk::cost() const { return 0.10 + _beverage->cost(); }