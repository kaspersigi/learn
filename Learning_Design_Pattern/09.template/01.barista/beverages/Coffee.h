#pragma once

#include "../interface/CaffeineBeverage.h"

class Coffee : public CaffeineBeverage
{
public:
    Coffee() = default;
    virtual ~Coffee() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;

protected:
    Coffee(const Coffee&) = delete;
    Coffee(Coffee&&) = delete;
    Coffee& operator = (const Coffee&) = delete;
    Coffee& operator = (Coffee&&) = delete;
};