#pragma once
#include "../menus/menus.h"

class Waitress {
public:
    Waitress(PancakeHouseMenu* pancakeHouseMenu, DinerMenu* dinerMenu);
    ~Waitress() = default;

    void printMenu() const;

protected:
    Waitress(const Waitress&) = delete;
    Waitress(Waitress&&) = delete;
    Waitress& operator=(const Waitress&) = delete;
    Waitress& operator=(Waitress&&) = delete;

private:
    std::shared_ptr<PancakeHouseMenu> _pancakeHouseMenu {};
    std::shared_ptr<DinerMenu> _dinerMenu {};
};