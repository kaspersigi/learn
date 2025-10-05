#include "Soy.h"

Soy::Soy(std::unique_ptr<Beverage> beverage)
    : _beverage(std::move(beverage))
{
}

std::string Soy::getDescription() const
{
    return _beverage->getDescription() + ", Soy";
}

double Soy::cost() const { return 0.15 + _beverage->cost(); }