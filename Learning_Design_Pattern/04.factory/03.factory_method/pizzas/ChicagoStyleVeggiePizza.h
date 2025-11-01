#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleVeggiePizza : public Pizza {
public:
    ChicagoStyleVeggiePizza();
    virtual ~ChicagoStyleVeggiePizza() = default;

    virtual void cut() const override;
};