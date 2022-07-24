#include "Mocha.h"

extern "C" {
#include "assert.h"
}

Mocha::Mocha(const Beverage* beverage)
    : _beverage(beverage)
{
    assert(beverage);
}

std::string Mocha::getDescription() const
{
    return _beverage->getDescription() + ", Mocha";
}

double Mocha::cost() const { return 0.20 + _beverage->cost(); }