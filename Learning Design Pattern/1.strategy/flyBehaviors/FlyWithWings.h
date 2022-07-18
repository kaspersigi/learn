#pragma once

#include "../interface/FlyBehavior.h"

class FlyWithWings : public FlyBehavior {
public:
    FlyWithWings() = default;

protected:
    virtual ~FlyWithWings() = default;
    FlyWithWings(const FlyWithWings&) = delete;
    FlyWithWings(FlyWithWings&&) = delete;
    FlyWithWings& operator=(const FlyWithWings&) = delete;
    FlyWithWings& operator=(FlyWithWings&&) = delete;

public:
    virtual void fly() const override;
};
