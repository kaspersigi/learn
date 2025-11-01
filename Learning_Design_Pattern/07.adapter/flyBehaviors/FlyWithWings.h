#pragma once

#include "../interface/FlyBehavior.h"

class FlyWithWings : public FlyBehavior {
public:
    FlyWithWings() = default;
    virtual ~FlyWithWings() = default;

    virtual void fly() const override;
};