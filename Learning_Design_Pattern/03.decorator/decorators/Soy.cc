#include "Soy.h"
#include "../interface/Beverage.h"

Soy::Soy(std::unique_ptr<Beverage> beverage)
    : _beverage(std::move(beverage))
{
}

Soy::~Soy() = default;

std::string Soy::getDescription() const
{
    return _beverage->getDescription() + ", Soy";
}

double Soy::cost() const { return 0.15 + _beverage->cost(); }