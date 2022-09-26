#pragma once

#include "../interface/FlyBehavior.h"

class FlyRocketPowered : public FlyBehavior {
public:
    FlyRocketPowered() = default;

    virtual void fly() const override;

protected:
    virtual ~FlyRocketPowered() = default;
    FlyRocketPowered(const FlyRocketPowered&) = delete;
    FlyRocketPowered(FlyRocketPowered&&) = delete;
    FlyRocketPowered& operator=(const FlyRocketPowered&) = delete;
    FlyRocketPowered& operator=(FlyRocketPowered&&) = delete;
};
