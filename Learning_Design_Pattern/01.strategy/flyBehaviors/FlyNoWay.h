#pragma once

#include "../interface/FlyBehavior.h"

class FlyNoWay : public FlyBehavior {
public:
    FlyNoWay() = default;

    virtual void fly() const override;

protected:
    virtual ~FlyNoWay() = default;
    FlyNoWay(const FlyNoWay&) = delete;
    FlyNoWay(FlyNoWay&&) = delete;
    FlyNoWay& operator=(const FlyNoWay&) = delete;
    FlyNoWay& operator=(FlyNoWay&&) = delete;
};
