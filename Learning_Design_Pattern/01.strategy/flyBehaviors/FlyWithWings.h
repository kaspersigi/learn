#pragma once

#include "../interface/FlyBehavior.h"

class FlyWithWings : public FlyBehavior
{
public:
    FlyWithWings() = default;

    virtual void fly() const override;

protected:
    virtual ~FlyWithWings() = default;
    FlyWithWings(const FlyWithWings&) = delete;
    FlyWithWings(FlyWithWings&&) = delete;
    FlyWithWings& operator = (const FlyWithWings&) = delete;
    FlyWithWings& operator = (FlyWithWings&&) = delete;
};
