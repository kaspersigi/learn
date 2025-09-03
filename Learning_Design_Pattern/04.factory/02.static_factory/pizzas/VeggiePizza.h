#pragma once

#include "../interface/Pizza.h"

class VeggiePizza : public Pizza
{
public:
    VeggiePizza();

protected:
    virtual ~VeggiePizza() = default;
    VeggiePizza(const VeggiePizza&) = delete;
    VeggiePizza(VeggiePizza&&) = delete;
    VeggiePizza& operator = (const VeggiePizza&) = delete;
    VeggiePizza& operator = (VeggiePizza&&) = delete;
};