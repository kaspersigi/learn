#pragma once

#include "../interface/Pizza.h"

class ClamPizza : public Pizza {
public:
    ClamPizza();

protected:
    virtual ~ClamPizza() = default;
    ClamPizza(const ClamPizza&) = delete;
    ClamPizza(ClamPizza&&) = delete;
    ClamPizza& operator=(const ClamPizza&) = delete;
    ClamPizza& operator=(ClamPizza&&) = delete;
};