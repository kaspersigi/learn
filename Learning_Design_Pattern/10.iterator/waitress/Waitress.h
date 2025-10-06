#pragma once

#include "../interface/NonCopyable.h"
#include "../menus/menus.h"
#include <memory>

class Waitress
{
public:
    Waitress(std::shared_ptr<PancakeHouseMenu> pancakeHouseMenu, std::shared_ptr<DinerMenu> dinerMenu);
    ~Waitress() = default;

    void printMenu() const;
    void printVegetarianMenu() const;
    bool isItemVegetarian(std::string name) const;

private:
    void printMenu(Iterator<MenuItem> & iterator) const;

    std::shared_ptr<PancakeHouseMenu> _pancakeHouseMenu;
    std::shared_ptr<DinerMenu> _dinerMenu;
};