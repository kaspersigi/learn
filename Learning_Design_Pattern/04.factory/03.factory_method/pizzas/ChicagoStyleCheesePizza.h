#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleCheesePizza : public Pizza
{
public:
    ChicagoStyleCheesePizza();
    virtual ~ChicagoStyleCheesePizza() = default;

    virtual void cut() const override;

protected:
    ChicagoStyleCheesePizza(const ChicagoStyleCheesePizza&) = delete;
    ChicagoStyleCheesePizza(ChicagoStyleCheesePizza&&) = delete;
    ChicagoStyleCheesePizza& operator = (const ChicagoStyleCheesePizza&) = delete;
    ChicagoStyleCheesePizza& operator = (ChicagoStyleCheesePizza&&) = delete;
};