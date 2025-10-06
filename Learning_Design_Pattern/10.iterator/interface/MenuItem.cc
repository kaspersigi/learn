#include "MenuItem.h"

MenuItem::MenuItem(std::string name, std::string description, bool vegetarian, double price)
    : _name(name)
    , _description(description)
    , _vegetarian(vegetarian)
    , _price(price)
{
}

std::string MenuItem::getName() const { return _name; }

std::string MenuItem::getDescription() const { return _description; }

double MenuItem::getPrice() const { return _price; }

bool MenuItem::isVegetarian() const { return _vegetarian; }

std::string MenuItem::toShow() const
{
    std::string value;
    value += _name + " $" + std::to_string(_price) + "\n" + _description;
    return value;
}