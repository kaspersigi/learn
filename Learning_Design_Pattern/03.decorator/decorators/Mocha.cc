#include "Mocha.h"
#include "../interface/Beverage.h"

Mocha::Mocha(std::unique_ptr<Beverage> beverage)
    : _beverage(std::move(beverage))
{
}

Mocha::~Mocha() = default;

std::string Mocha::getDescription() const
{
    return _beverage->getDescription() + ", Mocha";
}

double Mocha::cost() const { return 0.20 + _beverage->cost(); }