#include "Waitress.h"
#include <iostream>

Waitress::Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu)
    : _pancakeHouseMenu(pancakeHouseMenu)
    , _dinerMenu(dinerMenu)
{
}

void Waitress::printMenu() const
{
    Iterator<MenuItem>* pancakeIterator = _pancakeHouseMenu->createIterator();
    Iterator<MenuItem>* dinerIterator = _dinerMenu->createIterator();

    std::cout << "MENU\n----\nBREAKFAST" << std::endl;
    printMenu(pancakeIterator);
    std::cout << "\nLUNCH" << std::endl;
    printMenu(dinerIterator);
}

void Waitress::printMenu(Iterator<MenuItem>* iterator) const
{
    while (iterator->hasNext()) {
        auto menuItem = iterator->next();
        std::cout << menuItem->getName() << ", ";
        std::cout << menuItem->getPrice() << " -- ";
        std::cout << menuItem->getDescription() << std::endl;
    }
}

void Waitress::printVegetarianMenu() const
{
    printVegetarianMenu(_pancakeHouseMenu->createIterator());
    printVegetarianMenu(_dinerMenu->createIterator());
}

bool Waitress::isItemVegetarian(std::string name) const
{
    Iterator<MenuItem>* breakfastIterator = _pancakeHouseMenu->createIterator();
    if (isVegetarian(name, breakfastIterator)) {
        return true;
    }
    Iterator<MenuItem>* dinnerIterator = _dinerMenu->createIterator();
    if (isVegetarian(name, dinnerIterator)) {
        return true;
    }
    return false;
}

void Waitress::printVegetarianMenu(Iterator<MenuItem>* iterator) const
{
    while (iterator->hasNext()) {
        auto menuItem = iterator->next();
        if (menuItem->isVegetarian()) {
            std::cout << menuItem->getName() << ", ";
            std::cout << menuItem->getPrice() << " -- ";
            std::cout << menuItem->getDescription() << std::endl;
        }
    }
}

bool Waitress::isVegetarian(std::string name, Iterator<MenuItem>* iterator) const
{
    while (iterator->hasNext()) {
        auto menuItem = iterator->next();
        if (menuItem->getName().compare(name) == 0) {
            if (menuItem->isVegetarian()) {
                return true;
            }
        }
    }
    return false;
}