#include "Beverage.h"

Beverage::Beverage()
    : _description("Unknown Beverage")
{
}

std::string Beverage::getDescription() const { return _description; }