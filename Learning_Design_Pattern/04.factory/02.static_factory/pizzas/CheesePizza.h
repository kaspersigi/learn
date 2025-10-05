#pragma once

#include "../interface/Pizza.h"

class CheesePizza : public Pizza
{
public:
    CheesePizza();
    virtual ~CheesePizza() = default;
};