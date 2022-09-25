#pragma once

#include "../interface/Menu.h"
#include <string>
#include <vector>

class PancakeHouseMenu : public Menu {
public:
    PancakeHouseMenu();
    virtual ~PancakeHouseMenu() = default;

    void addItem(std::string name, std::string description, bool vegetarian, double price);
    std::vector<MenuItem*> getMenuItems() const;
    virtual Iterator<MenuItem>* createIterator() const override;
    std::string toShow() const;

protected:
    PancakeHouseMenu(const PancakeHouseMenu&) = delete;
    PancakeHouseMenu(PancakeHouseMenu&&) = delete;
    PancakeHouseMenu& operator=(const PancakeHouseMenu&) = delete;
    PancakeHouseMenu& operator=(PancakeHouseMenu&&) = delete;

private:
    std::vector<MenuItem*> _menuItems {};
};