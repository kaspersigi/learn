#pragma once

#include "NonCopyable.h"
#include <string>

class Beverage : public NonCopyable {
public:
    virtual ~Beverage() = default;

    virtual std::string getDescription() const;
    virtual double cost() const = 0;

protected:
    Beverage();

protected:
    std::string _description {};
};