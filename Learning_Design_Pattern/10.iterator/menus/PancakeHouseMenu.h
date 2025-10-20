#pragma once

#include "../interface/Menu.h"
#include <string>
#include <vector>

class PancakeHouseMenu : public Menu
{
public:
    PancakeHouseMenu();
    virtual ~PancakeHouseMenu() = default;

    void addItem(const std::string& name, const std::string& description, bool vegetarian, double price);
    virtual std::unique_ptr<Iterator<MenuItem>> createIterator() const override;

private:
    std::vector<std::shared_ptr<MenuItem>> _menuItems {};
};