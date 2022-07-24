#pragma once

#include "../interface/Beverage.h"

class Espresso : public Beverage {
public:
    Espresso();
    virtual ~Espresso() = default;

protected:
    Espresso(const Espresso&) = delete;
    Espresso(Espresso&&) = delete;
    Espresso& operator=(const Espresso&) = delete;
    Espresso& operator=(Espresso&&) = delete;

public:
    virtual double cost() const override;
};