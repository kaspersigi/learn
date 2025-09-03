#pragma once

#include "../interface/Pizza.h"

class NYStyleClamPizza : public Pizza
{
public:
    NYStyleClamPizza();
    virtual ~NYStyleClamPizza() = default;

protected:
    NYStyleClamPizza(const NYStyleClamPizza&) = delete;
    NYStyleClamPizza(NYStyleClamPizza&&) = delete;
    NYStyleClamPizza& operator = (const NYStyleClamPizza&) = delete;
    NYStyleClamPizza& operator = (NYStyleClamPizza&&) = delete;
};