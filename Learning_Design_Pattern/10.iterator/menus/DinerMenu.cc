#include "DinerMenu.h"
#include <iostream>

DinerMenu::DinerMenu()
{
    for (int i = 0; i < MAX_ITEMS; i++) {
        _menuItems[i] = nullptr;
    }
    addItem("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
    addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
    addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
    addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
    addItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
    addItem("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89);
}

DinerMenu::~DinerMenu()
{
    for (int i = 0; i < MAX_ITEMS; i++) {
        delete _menuItems[i];
    }
}

void DinerMenu::addItem(std::string name, std::string description, bool vegetarian, double price)
{
    auto menuItem = new MenuItem(name, description, vegetarian, price);

    if (_numberOfItems >= MAX_ITEMS) {
        std::cerr << "Sorry, menu is full!  Can't add item to menu" << std::endl;
    } else {
        _menuItems[_numberOfItems] = menuItem;
        _numberOfItems++;
    }
}

std::size_t DinerMenu::length() const
{
    return _numberOfItems + 1;
}

DinerMenuIterator DinerMenu::begin()
{
    return DinerMenuIterator(_menuItems[0]);
}

DinerMenuIterator DinerMenu::end()
{
    return DinerMenuIterator(_menuItems[_numberOfItems]);
}