#pragma once

#include "../interface/Pizza.h"

class NYStyleCheesePizza : public Pizza {
public:
    NYStyleCheesePizza();
    virtual ~NYStyleCheesePizza() = default;

protected:
    NYStyleCheesePizza(const NYStyleCheesePizza&) = delete;
    NYStyleCheesePizza(NYStyleCheesePizza&&) = delete;
    NYStyleCheesePizza& operator=(const NYStyleCheesePizza&) = delete;
    NYStyleCheesePizza& operator=(NYStyleCheesePizza&&) = delete;
};