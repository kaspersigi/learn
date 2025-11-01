#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleClamPizza : public Pizza {
public:
    ChicagoStyleClamPizza();
    virtual ~ChicagoStyleClamPizza() = default;

    virtual void cut() const override;
};