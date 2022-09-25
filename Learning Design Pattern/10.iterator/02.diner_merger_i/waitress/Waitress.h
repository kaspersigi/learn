#pragma once
#include "../menus/menus.h"

class Waitress {
public:
    Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu);
    ~Waitress() = default;

    void printMenu() const;
    void printMenu(Iterator<MenuItem>* iterator) const;
    void printVegetarianMenu() const;
    bool isItemVegetarian(std::string name) const;
    void printVegetarianMenu(Iterator<MenuItem>* iterator) const;
    bool isVegetarian(std::string name, Iterator<MenuItem>* iterator) const;

protected:
    Waitress(const Waitress&) = delete;
    Waitress(Waitress&&) = delete;
    Waitress& operator=(const Waitress&) = delete;
    Waitress& operator=(Waitress&&) = delete;

private:
    std::shared_ptr<PancakeHouseMenu> _pancakeHouseMenu;
    std::shared_ptr<DinerMenu> _dinerMenu;
};