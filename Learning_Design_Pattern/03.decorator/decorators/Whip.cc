#include "Whip.h"

extern "C" {
#include "assert.h"
}

Whip::Whip(const Beverage* beverage)
    : _beverage(beverage)
{
    assert(beverage);
}

std::string Whip::getDescription() const
{
    return _beverage->getDescription() + ", Whip";
}

double Whip::cost() const { return 0.10 + _beverage->cost(); }