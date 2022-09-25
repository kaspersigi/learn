#pragma

#include "../interface/Menu.h"
#include <string>

class DinerMenu : public Menu {
public:
    DinerMenu();
    virtual ~DinerMenu() = default;

    void addItem(std::string name, std::string description, bool vegetarian, double price);
    MenuItem** getMenuItems() const;
    virtual Iterator<MenuItem>* createIterator() const override;

protected:
    DinerMenu(const DinerMenu&) = delete;
    DinerMenu(DinerMenu&&) = delete;
    DinerMenu& operator=(const DinerMenu&) = delete;
    DinerMenu& operator=(DinerMenu&&) = delete;

private:
    static const int MAX_ITEMS { 6 };
    int _numberOfItems { 0 };
    MenuItem** _menuItems { nullptr };
};