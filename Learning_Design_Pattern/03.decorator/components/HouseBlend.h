#pragma once

#include "../interface/Beverage.h"

class HouseBlend : public Beverage {
public:
    HouseBlend();
    virtual ~HouseBlend() = default;

    virtual double cost() const override;
};