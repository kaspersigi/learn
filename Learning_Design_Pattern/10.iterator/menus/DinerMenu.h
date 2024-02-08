#pragma once

#include "../interface/Menu.h"
#include "../iterators/DinerMenuIterator.h"
#include <memory>
#include <string>

class DinerMenu : public Menu {
public:
    DinerMenu();
    virtual ~DinerMenu();

    void addItem(std::string name, std::string description, bool vegetarian, double price);
    std::size_t length() const;
    DinerMenuIterator begin();
    DinerMenuIterator end();

protected:
    DinerMenu(const DinerMenu&) = delete;
    DinerMenu(DinerMenu&&) = delete;
    DinerMenu& operator=(const DinerMenu&) = delete;
    DinerMenu& operator=(DinerMenu&&) = delete;

private:
    static const std::size_t MAX_ITEMS { 6 };
    MenuItem* _menuItems[MAX_ITEMS];
    std::size_t _numberOfItems { 0 };
};