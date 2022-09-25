#include "PancakeHouseMenu.h"
#include "../iterators/PancakeHouseMenuIterator.h"
#include <iostream>

PancakeHouseMenu::PancakeHouseMenu()
{
    addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
    addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
    addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
    addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
}

void PancakeHouseMenu::addItem(std::string name, std::string description, bool vegetarian, double price)
{
    MenuItem* menuItem = new MenuItem(name, description, vegetarian, price);
    _menuItems.push_back(menuItem);
}

std::vector<MenuItem*> PancakeHouseMenu::getMenuItems() const { return _menuItems; }

Iterator<MenuItem>* PancakeHouseMenu::createIterator() const { return new PancakeHouseMenuIterator(_menuItems); }

std::string PancakeHouseMenu::toShow() const
{
    return "Objectville Pancake House Menu";
}