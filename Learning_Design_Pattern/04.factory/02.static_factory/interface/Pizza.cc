#include "Pizza.h"
#include <algorithm>

void Pizza::prepare() const
{
    std::cout << "Preparing " + _name << std::endl;
}

void Pizza::Pizza::bake() const
{
    std::cout << "Baking " + _name << std::endl;
}

void Pizza::cut() const
{
    std::cout << "Cutting " + _name << std::endl;
}

void Pizza::box() const
{
    std::cout << "Boxing " + _name << std::endl;
}

std::string Pizza::getName() const { return _name; }

std::string Pizza::toShow() const
{
    std::string value;
    value += "---- " + _name + " ----" + "\n";
    value += _dough + "\n";
    value += _sauce + "\n";

    std::for_each(_toppings.cbegin(), _toppings.cend(), [&](auto const& e) { value += e + "\n"; });

    return value;
}