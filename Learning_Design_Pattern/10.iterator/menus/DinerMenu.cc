#include "DinerMenu.h"
#include "../iterators/DinerMenuIterator.h"

DinerMenu::DinerMenu()
{
    addItem("Vegetarian BLT", "(Fakin'') Bacon with lettuce & tomato on whole wheat", true, 2.99);
    addItem("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
    addItem("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
    addItem("Hotdog", "A hot dog, with saurkraut, relish, onions, topped with cheese", false, 3.05);
    addItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
    addItem("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89);
}

void DinerMenu::addItem(const std::string& name, const std::string& description, bool vegetarian, double price)
{
    auto menuItem = std::make_shared<MenuItem>(name, description, vegetarian, price);
    _menuItems.push_back(menuItem);
}

std::unique_ptr<Iterator<MenuItem>> DinerMenu::createIterator() const
{
    return std::make_unique<DinerMenuIterator>(_menuItems);
}