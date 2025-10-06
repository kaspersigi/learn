#include "PancakeHouseMenu.h"
#include "../iterators/PancakeHouseMenuIterator.h"

PancakeHouseMenu::PancakeHouseMenu()
{
    addItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
    addItem("Regular Pancake Breakfast", "Pancakes with fried eggs, sausage", false, 2.99);
    addItem("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
    addItem("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
}

void PancakeHouseMenu::addItem(std::string name, std::string description, bool vegetarian, double price)
{
    auto menuItem = std::make_shared<MenuItem>(name, description, vegetarian, price);
    _menuItems.push_back(menuItem);
}

std::unique_ptr<Iterator<MenuItem>> PancakeHouseMenu::createIterator() const
{
    return std::make_unique<PancakeHouseMenuIterator>(_menuItems);
}