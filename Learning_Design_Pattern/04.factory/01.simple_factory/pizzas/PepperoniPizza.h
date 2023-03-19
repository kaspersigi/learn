#pragma once

#include "../interface/Pizza.h"

class PepperoniPizza : public Pizza {
public:
    PepperoniPizza();

protected:
    virtual ~PepperoniPizza() = default;
    PepperoniPizza(const PepperoniPizza&) = delete;
    PepperoniPizza(PepperoniPizza&&) = delete;
    PepperoniPizza& operator=(const PepperoniPizza&) = delete;
    PepperoniPizza& operator=(PepperoniPizza&&) = delete;
};