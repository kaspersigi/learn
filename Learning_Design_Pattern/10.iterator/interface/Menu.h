#pragma once

#include "MenuItem.h"

class Menu {
public:
    virtual ~Menu() = default;

protected:
    Menu() = default;
    Menu(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator=(const Menu&) = delete;
    Menu& operator=(Menu&&) = delete;
};