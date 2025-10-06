#pragma once

#include "../interface/FlyBehavior.h"

class FlyNoWay : public FlyBehavior
{
public:
    FlyNoWay() = default;
    virtual ~FlyNoWay() = default;

    virtual void fly() const override;
};