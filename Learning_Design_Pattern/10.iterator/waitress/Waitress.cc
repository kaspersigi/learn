#include "Waitress.h"
#include <iostream>

Waitress::Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu)
    : _pancakeHouseMenu(pancakeHouseMenu)
    , _dinerMenu(dinerMenu)
{
}

void Waitress::printMenu() const
{
    std::cout << "MENU\n----\nBREAKFAST" << std::endl;
    _pancakeHouseMenu->begin()->toShow();
#if 0
    for (auto i = _pancakeHouseMenu->begin(); i != _pancakeHouseMenu->end(); ++i) {
        i->toShow();
    }
    std::cout << "\nLUNCH" << std::endl;
    for (auto i = _dinerMenu->begin(); i != _pancakeHouseMenu->end(); ++i) {
        i->toShow();
    }
#endif
}