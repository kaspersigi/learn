#pragma once

#include "../interface/Pizza.h"

class ChicagoStylePepperoniPizza : public Pizza {
public:
    ChicagoStylePepperoniPizza();
    virtual ~ChicagoStylePepperoniPizza() = default;

    virtual void cut() const override;
};