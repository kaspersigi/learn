#pragma once

#include "../interface/NonCopyable.h"
#include <memory>

class PancakeHouseMenu;
class DinerMenu;
class MenuItem;
template <typename T>
class Iterator;
class WaitressImpl;

class Waitress {
public:
    Waitress(const std::shared_ptr<PancakeHouseMenu>& pancakeHouseMenu, const std::shared_ptr<DinerMenu>& dinerMenu);
    ~Waitress();

    void printMenu() const;
    void printVegetarianMenu() const;
    bool isItemVegetarian(const std::string& name) const;

private:
    std::unique_ptr<WaitressImpl> _impl;
};