#pragma once

#include "../interface/FlyBehavior.h"

class FlyRocketPowered : public FlyBehavior
{
public:
    FlyRocketPowered() = default;
    virtual ~FlyRocketPowered() = default;

    virtual void fly() const override;
};
