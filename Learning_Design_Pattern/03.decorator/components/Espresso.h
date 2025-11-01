#pragma once

#include "../interface/Beverage.h"

class Espresso : public Beverage {
public:
    Espresso();
    virtual ~Espresso() = default;

    virtual double cost() const override;
};