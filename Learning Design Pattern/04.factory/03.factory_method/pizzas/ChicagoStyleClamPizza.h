#pragma once

#include "../interface/Pizza.h"

class ChicagoStyleClamPizza : public Pizza {
public:
    ChicagoStyleClamPizza();
    virtual ~ChicagoStyleClamPizza() = default;

    virtual void cut() const override;

protected:
    ChicagoStyleClamPizza(const ChicagoStyleClamPizza&) = delete;
    ChicagoStyleClamPizza(ChicagoStyleClamPizza&&) = delete;
    ChicagoStyleClamPizza& operator=(const ChicagoStyleClamPizza&) = delete;
    ChicagoStyleClamPizza& operator=(ChicagoStyleClamPizza&&) = delete;
};