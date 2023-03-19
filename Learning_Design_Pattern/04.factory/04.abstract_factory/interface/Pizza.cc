#include "Pizza.h"
#include <algorithm>

Pizza::~Pizza()
{
    std::for_each(_veggies.begin(), _veggies.end(), [](auto e) { delete e; });
    std::vector<Veggies*>().swap(_veggies);
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

void Pizza::setName(std::string name) { _name = name; }

std::string Pizza::toShow() const
{
    std::string value;
    value += "\"" + _name + "\"" + "\n";
    if (_dough.get())
        value += _dough->toShow() + "\n";

    if (_sauce.get())
        value += _sauce->toShow() + "\n";

    if (_cheese.get())
        value += _cheese->toShow() + "\n";

    if (_clam.get())
        value += _clam->toShow() + "\n";

    if (_pepperoni.get())
        value += _pepperoni->toShow() + "\n";

    if (!_veggies.empty())
        std::for_each(_veggies.cbegin(), _veggies.cend(), [&](auto e) { value += e->toShow() + "\n"; });

    return value;
}