#pragma once

#include "Beverage.h"

class CondimentDecorator : public Beverage {
public:
    virtual ~CondimentDecorator() = default;

protected:
    CondimentDecorator() = default;
    CondimentDecorator(const CondimentDecorator&) = delete;
    CondimentDecorator(CondimentDecorator&&) = delete;
    CondimentDecorator& operator=(const CondimentDecorator&) = delete;
    CondimentDecorator& operator=(const CondimentDecorator&&) = delete;

public:
    virtual std::string getDescription() const = 0;
};