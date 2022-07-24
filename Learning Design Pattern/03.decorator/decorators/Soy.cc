#include "Soy.h"

extern "C" {
#include "assert.h"
}

Soy::Soy(const Beverage* beverage)
    : _beverage(beverage)
{
    assert(beverage);
}

std::string Soy::getDescription() const
{
    return _beverage->getDescription() + ", Soy";
}

double Soy::cost() const { return 0.15 + _beverage->cost(); }