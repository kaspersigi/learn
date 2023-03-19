#pragma once

#include <string>

class Beverage {
public:
    virtual ~Beverage() = default;

    virtual std::string getDescription() const;
    virtual double cost() const = 0;

protected:
    Beverage();
    Beverage(const Beverage&) = delete;
    Beverage(Beverage&&) = delete;
    Beverage& operator=(const Beverage&) = delete;
    Beverage& operator=(Beverage&&) = delete;

protected:
    std::string _description {};
};