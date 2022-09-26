#pragma once

#include "../interface/Beverage.h"

class Espresso : public Beverage {
public:
    Espresso();
    virtual ~Espresso() = default;

    virtual double cost() const override;

protected:
    Espresso(const Espresso&) = delete;
    Espresso(Espresso&&) = delete;
    Espresso& operator=(const Espresso&) = delete;
    Espresso& operator=(Espresso&&) = delete;
};