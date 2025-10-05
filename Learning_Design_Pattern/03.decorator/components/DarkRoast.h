#pragma once

#include "../interface/Beverage.h"

class DarkRoast : public Beverage
{
public:
    DarkRoast();
    virtual ~DarkRoast() = default;

    virtual double cost() const override;
};