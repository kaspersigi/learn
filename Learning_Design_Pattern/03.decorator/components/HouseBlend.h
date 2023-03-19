#pragma once

#include "../interface/Beverage.h"

class HouseBlend : public Beverage {
public:
    HouseBlend();
    virtual ~HouseBlend() = default;

    virtual double cost() const override;

protected:
    HouseBlend(const HouseBlend&) = delete;
    HouseBlend(HouseBlend&&) = delete;
    HouseBlend& operator=(const HouseBlend&) = delete;
    HouseBlend& operator=(HouseBlend&&) = delete;
};