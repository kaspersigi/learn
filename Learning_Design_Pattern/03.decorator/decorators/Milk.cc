#include "Milk.h"
#include "../interface/Beverage.h"

Milk::Milk(std::unique_ptr<Beverage> beverage)
    : _beverage(std::move(beverage))
{
}

Milk::~Milk() = default;

std::string Milk::getDescription() const
{
    return _beverage->getDescription() + ", Milk";
}

double Milk::cost() const { return 0.10 + _beverage->cost(); }