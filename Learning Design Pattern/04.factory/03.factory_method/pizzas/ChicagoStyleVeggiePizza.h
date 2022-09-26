#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleVeggiePizza : public Pizza {
public:
    ChicagoStyleVeggiePizza();
    virtual ~ChicagoStyleVeggiePizza() = default;

    virtual void cut() const override;

protected:
    ChicagoStyleVeggiePizza(const ChicagoStyleVeggiePizza&) = delete;
    ChicagoStyleVeggiePizza(ChicagoStyleVeggiePizza&&) = delete;
    ChicagoStyleVeggiePizza& operator=(const ChicagoStyleVeggiePizza&) = delete;
    ChicagoStyleVeggiePizza& operator=(ChicagoStyleVeggiePizza&&) = delete;
};