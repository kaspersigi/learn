#pragma once

#include "NonCopyable.h"
#include <string>

class MenuItem : public NonCopyable {
public:
    MenuItem(std::string name, std::string description, bool vegetarian, double price);
    virtual ~MenuItem() = default;

    std::string getName() const;
    std::string getDescription() const;
    double getPrice() const;
    bool isVegetarian() const;
    std::string toShow() const;

private:
    std::string _name {};
    std::string _description {};
    bool _vegetarian {};
    double _price {};
};