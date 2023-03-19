#pragma once

#include "../interface/Pizza.h"

class NYStylePepperoniPizza : public Pizza {
public:
    NYStylePepperoniPizza();
    virtual ~NYStylePepperoniPizza() = default;

protected:
    NYStylePepperoniPizza(const NYStylePepperoniPizza&) = delete;
    NYStylePepperoniPizza(NYStylePepperoniPizza&&) = delete;
    NYStylePepperoniPizza& operator=(const NYStylePepperoniPizza&) = delete;
    NYStylePepperoniPizza& operator=(NYStylePepperoniPizza&&) = delete;
};