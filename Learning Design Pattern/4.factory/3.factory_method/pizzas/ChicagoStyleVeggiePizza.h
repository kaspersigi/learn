#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleVeggiePizza : public Pizza {
public:
    ChicagoStyleVeggiePizza();
    virtual ~ChicagoStyleVeggiePizza() = default;

protected:
    ChicagoStyleVeggiePizza(const ChicagoStyleVeggiePizza&) = delete;
    ChicagoStyleVeggiePizza(ChicagoStyleVeggiePizza&&) = delete;
    ChicagoStyleVeggiePizza& operator=(const ChicagoStyleVeggiePizza&) = delete;
    ChicagoStyleVeggiePizza& operator=(ChicagoStyleVeggiePizza&&) = delete;

public:
    virtual void cut() const override;
};