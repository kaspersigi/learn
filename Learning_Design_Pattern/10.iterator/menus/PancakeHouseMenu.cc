#include "PancakeHouseMenu.h"

PancakeHouseMenu::PancakeHouseMenu()
{
    addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
    addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
    addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
    addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
}

void PancakeHouseMenu::addItem(std::string name, std::string description, bool vegetarian, double price)
{
    _menuItems.push_back(new MenuItem(name, description, vegetarian, price));
}

std::string PancakeHouseMenu::toShow() const
{
    return "Objectville Pancake House Menu";
}

std::size_t PancakeHouseMenu::length() const
{
    return _menuItems.size();
}

PancakeHouseMenuIterator PancakeHouseMenu::begin()
{
    return PancakeHouseMenuIterator(_menuItems[0]);
}

PancakeHouseMenuIterator PancakeHouseMenu::end()
{
    return PancakeHouseMenuIterator(_menuItems[_menuItems.size() - 1]);
}