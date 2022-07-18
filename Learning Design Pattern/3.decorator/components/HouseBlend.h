#pragma once

#include "../interface/Beverage.h"

class HouseBlend : public Beverage {
public:
    HouseBlend();
    virtual ~HouseBlend() = default;

protected:
    HouseBlend(const HouseBlend&) = delete;
    HouseBlend(HouseBlend&&) = delete;
    HouseBlend& operator=(const HouseBlend&) = delete;
    HouseBlend& operator=(HouseBlend&&) = delete;

public:
    virtual double cost() const override;
};