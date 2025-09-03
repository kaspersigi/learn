#pragma once

#include "Iterator.h"
#include "MenuItem.h"

class Menu
{
public:
    virtual ~Menu() = default;

    virtual Iterator<MenuItem>* createIterator() const = 0;

protected:
    Menu() = default;
    Menu(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator = (const Menu&) = delete;
    Menu& operator = (Menu&&) = delete;
};