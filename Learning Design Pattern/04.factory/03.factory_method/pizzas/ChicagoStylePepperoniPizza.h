#pragma once

#include "../interface/Pizza.h"

class ChicagoStylePepperoniPizza : public Pizza {
public:
    ChicagoStylePepperoniPizza();
    virtual ~ChicagoStylePepperoniPizza() = default;

protected:
    ChicagoStylePepperoniPizza(const ChicagoStylePepperoniPizza&) = delete;
    ChicagoStylePepperoniPizza(ChicagoStylePepperoniPizza&&) = delete;
    ChicagoStylePepperoniPizza& operator=(const ChicagoStylePepperoniPizza&) = delete;
    ChicagoStylePepperoniPizza& operator=(ChicagoStylePepperoniPizza&&) = delete;

public:
    virtual void cut() const override;
};