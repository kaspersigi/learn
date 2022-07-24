#pragma once

#include "../interface/Pizza.h"

class CheesePizza : public Pizza {
public:
    CheesePizza();

protected:
    virtual ~CheesePizza() = default;
    CheesePizza(const CheesePizza&) = delete;
    CheesePizza(CheesePizza&&) = delete;
    CheesePizza& operator=(const CheesePizza&) = delete;
    CheesePizza& operator=(CheesePizza&&) = delete;
};