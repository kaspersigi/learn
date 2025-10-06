#include "Pizza.h"
#include <algorithm>

Pizza::~Pizza() = default;

void Pizza::bake() const
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

void Pizza::setName(std::string name) { _name = name; }

std::string Pizza::toShow() const
{
    std::string value;
    value += "\"" + _name + "\"" + "\n";
    if (_dough)
        value += _dough->toShow() + "\n";

    if (_sauce)
        value += _sauce->toShow() + "\n";

    if (_cheese)
        value += _cheese->toShow() + "\n";

    if (_clam)
        value += _clam->toShow() + "\n";

    if (_pepperoni)
        value += _pepperoni->toShow() + "\n";

    if (!_veggies.empty())
        std::for_each(_veggies.cbegin(), _veggies.cend(),
            [&](const auto& e) { value += e->toShow() + "\n"; });

    return value;
}