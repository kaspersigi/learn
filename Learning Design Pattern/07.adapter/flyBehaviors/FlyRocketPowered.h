#pragma once

#include "../interface/FlyBehavior.h"

class FlyRocketPowered : public FlyBehavior {
public:
    FlyRocketPowered() = default;

protected:
    virtual ~FlyRocketPowered() = default;
    FlyRocketPowered(const FlyRocketPowered&) = delete;
    FlyRocketPowered(FlyRocketPowered&&) = delete;
    FlyRocketPowered& operator=(const FlyRocketPowered&) = delete;
    FlyRocketPowered& operator=(FlyRocketPowered&&) = delete;

public:
    virtual void fly() const override;
};
