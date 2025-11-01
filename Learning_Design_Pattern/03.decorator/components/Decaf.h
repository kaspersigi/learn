#pragma once

#include "../interface/Beverage.h"

class Decaf : public Beverage {
public:
    Decaf();
    virtual ~Decaf() = default;

    virtual double cost() const override;
};