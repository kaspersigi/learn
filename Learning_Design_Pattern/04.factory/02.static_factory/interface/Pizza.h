#pragma once

#include <iostream>
#include <list>

class Pizza {
public:
    virtual ~Pizza() = default;

    virtual void prepare() const;
    virtual void bake() const;
    virtual void cut() const;
    virtual void box() const;
    std::string getName() const;
    std::string toShow() const;

protected:
    Pizza() = default;
    Pizza(const Pizza&) = delete;
    Pizza(Pizza&&) = delete;
    Pizza& operator=(const Pizza&) = delete;
    Pizza& operator=(Pizza&&) = delete;

    std::string _name {};
    std::string _dough {};
    std::string _sauce {};
    mutable std::list<std::string> _toppings {};
};