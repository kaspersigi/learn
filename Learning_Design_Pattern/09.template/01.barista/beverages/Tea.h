#pragma once

#include "../interface/CaffeineBeverage.h"

class Tea : public CaffeineBeverage
{
public:
    Tea() = default;
    virtual ~Tea() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;
};