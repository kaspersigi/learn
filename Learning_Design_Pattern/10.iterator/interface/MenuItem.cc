#include "MenuItem.h"

MenuItem::MenuItem(std::string name, std::string description, bool vegetarian, double price)
    : _name(name)
    , _description(description)
    , _vegetarian(vegetarian)
    , _price(price)
{
}

std::string MenuItem::getName() { return _name; }

std::string MenuItem::getDescription() { return _description; }

double MenuItem::getPrice() { return _price; }

bool MenuItem::isVegetarian() { return _vegetarian; }

std::string MenuItem::toShow()
{
    std::string value;
    value += _name + " $" + std::to_string(_price) + "\n" + _description;
    return value;
}