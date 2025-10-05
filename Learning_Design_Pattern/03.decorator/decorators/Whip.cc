#include "Whip.h"

Whip::Whip(std::unique_ptr<Beverage> beverage)
    : _beverage(std::move(beverage))
{
}

std::string Whip::getDescription() const
{
    return _beverage->getDescription() + ", Whip";
}

double Whip::cost() const { return 0.10 + _beverage->cost(); }