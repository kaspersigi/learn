#pragma once

#include "../interface/Pizza.h"

class NYStyleVeggiePizza : public Pizza
{
public:
    NYStyleVeggiePizza();
    virtual ~NYStyleVeggiePizza() = default;

protected:
    NYStyleVeggiePizza(const NYStyleVeggiePizza&) = delete;
    NYStyleVeggiePizza(NYStyleVeggiePizza&&) = delete;
    NYStyleVeggiePizza& operator = (const NYStyleVeggiePizza&) = delete;
    NYStyleVeggiePizza& operator = (NYStyleVeggiePizza&&) = delete;
};