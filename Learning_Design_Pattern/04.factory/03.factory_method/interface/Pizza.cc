#include "Pizza.h"
#include <algorithm>

void Pizza::prepare() const
{
    std::cout << "Preparing " << _name << std::endl;
    std::cout << "Tossing dough..." << std::endl;
    std::cout << "Adding sauce..." << std::endl;
    std::cout << "Adding toppings: " << std::endl;
    std::for_each(_toppings.cbegin(), _toppings.cend(), [&](auto e) { std::cout << "   " << e << std::endl; });
}

void Pizza::Pizza::bake() const
{
    std::cout << "Bake for 25 minutes at 350" << std::endl;
}

void Pizza::cut() const
{
    std::cout << "Cutting the pizza into diagonal slices" << std::endl;
}

void Pizza::box() const
{
    std::cout << "Place pizza in official PizzaStore box" << std::endl;
}

std::string Pizza::getName() const { return _name; }

std::string Pizza::toShow() const
{
    std::string value;
    value += "---- " + _name + " ----" + "\n";
    value += _dough + "\n";
    value += _sauce + "\n";

    std::for_each(_toppings.cbegin(), _toppings.cend(), [&](auto e) { value += e + "\n"; });

    return value;
}