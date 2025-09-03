#pragma once

#include <string>

class MenuItem
{
public:
    MenuItem(std::string name, std::string description, bool vegetarian, double price);
    virtual ~MenuItem() = default;

    std::string getName();
    std::string getDescription();
    double getPrice();
    bool isVegetarian();
    std::string toShow();

protected:
    MenuItem(const MenuItem&) = delete;
    MenuItem(MenuItem&&) = delete;
    MenuItem& operator = (const MenuItem&) = delete;
    MenuItem& operator = (MenuItem&&) = delete;

private:
    std::string _name {};
    std::string _description {};
    bool _vegetarian {};
    double _price {};
};