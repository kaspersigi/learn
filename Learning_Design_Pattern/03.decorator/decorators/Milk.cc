#include "Milk.h"

Milk::Milk(std::unique_ptr<Beverage> beverage)
    : _beverage(std::move(beverage))
{
}

std::string Milk::getDescription() const
{
    return _beverage->getDescription() + ", Milk";
}

double Milk::cost() const { return 0.10 + _beverage->cost(); }