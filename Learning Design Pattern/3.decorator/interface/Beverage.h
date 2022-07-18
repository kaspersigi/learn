#pragma once

#include <string>

class Beverage {
public:
    virtual ~Beverage() = default;

protected:
    Beverage();
    Beverage(const Beverage&) = delete;
    Beverage(Beverage&&) = delete;
    Beverage& operator=(const Beverage&) = delete;
    Beverage& operator=(Beverage&&) = delete;

public:
    virtual std::string getDescription() const;
    virtual double cost() const = 0;

protected:
    std::string _description;
};