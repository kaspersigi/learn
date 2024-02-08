#pragma once

#include "../interface/Menu.h"
#include "../iterators/PancakeHouseMenuIterator.h"
#include <vector>

class PancakeHouseMenu : public Menu {
public:
    PancakeHouseMenu();
    virtual ~PancakeHouseMenu() = default;

    void addItem(std::string name, std::string description, bool vegetarian, double price);
    std::string toShow() const;
    std::size_t length() const;
    PancakeHouseMenuIterator begin();
    PancakeHouseMenuIterator end();

protected:
    PancakeHouseMenu(const PancakeHouseMenu&) = delete;
    PancakeHouseMenu(PancakeHouseMenu&&) = delete;
    PancakeHouseMenu& operator=(const PancakeHouseMenu&) = delete;
    PancakeHouseMenu& operator=(PancakeHouseMenu&&) = delete;

private:
    std::vector<MenuItem*> _menuItems;
};