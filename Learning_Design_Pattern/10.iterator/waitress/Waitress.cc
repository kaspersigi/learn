#include "Waitress.h"
#include <iostream>

Waitress::Waitress(std::shared_ptr<PancakeHouseMenu> pancakeHouseMenu, std::shared_ptr<DinerMenu> dinerMenu)
    : _pancakeHouseMenu(pancakeHouseMenu)
    , _dinerMenu(dinerMenu)
{
}

void Waitress::printMenu() const
{
    auto pancakeIterator = _pancakeHouseMenu->createIterator();
    auto dinerIterator = _dinerMenu->createIterator();

    std::cout << "MENU\n----\nBREAKFAST" << std::endl;
    printMenu(*pancakeIterator);
    std::cout << "\nLUNCH" << std::endl;
    printMenu(*dinerIterator);
}

void Waitress::printVegetarianMenu() const
{
    std::cout << "\nVEGETARIAN MENU\n----\nBREAKFAST" << std::endl;
    auto pancakeIterator = _pancakeHouseMenu->createIterator();
    while (pancakeIterator->hasNext()) {
        const auto& menuItem = pancakeIterator->next();
        if (menuItem.isVegetarian()) {
            std::cout << menuItem.getName() << ", ";
            std::cout << menuItem.getPrice() << " -- ";
            std::cout << menuItem.getDescription() << std::endl;
        }
    }

    std::cout << "\nLUNCH" << std::endl;
    auto dinerIterator = _dinerMenu->createIterator();
    while (dinerIterator->hasNext()) {
        const auto& menuItem = dinerIterator->next();
        if (menuItem.isVegetarian()) {
            std::cout << menuItem.getName() << ", ";
            std::cout << menuItem.getPrice() << " -- ";
            std::cout << menuItem.getDescription() << std::endl;
        }
    }
}

bool Waitress::isItemVegetarian(std::string name) const
{
    auto breakfastIterator = _pancakeHouseMenu->createIterator();
    while (breakfastIterator->hasNext()) {
        const auto& menuItem = breakfastIterator->next();
        if (menuItem.getName().compare(name) == 0) {
            if (menuItem.isVegetarian()) {
                return true;
            }
        }
    }

    auto dinnerIterator = _dinerMenu->createIterator();
    while (dinnerIterator->hasNext()) {
        const auto& menuItem = dinnerIterator->next();
        if (menuItem.getName().compare(name) == 0) {
            if (menuItem.isVegetarian()) {
                return true;
            }
        }
    }
    return false;
}

void Waitress::printMenu(Iterator<MenuItem>& iterator) const
{
    while (iterator.hasNext()) {
        const auto& menuItem = iterator.next();
        std::cout << menuItem.getName() << ", ";
        std::cout << menuItem.getPrice() << " -- ";
        std::cout << menuItem.getDescription() << std::endl;
    }
}