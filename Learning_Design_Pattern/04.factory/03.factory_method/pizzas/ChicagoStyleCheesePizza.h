#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleCheesePizza : public Pizza
{
public:
    ChicagoStyleCheesePizza();
    virtual ~ChicagoStyleCheesePizza() = default;

    virtual void cut() const override;
};