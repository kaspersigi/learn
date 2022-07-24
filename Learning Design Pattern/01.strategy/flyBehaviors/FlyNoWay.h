#pragma once

#include "../interface/FlyBehavior.h"

class FlyNoWay : public FlyBehavior {
public:
    FlyNoWay() = default;

protected:
    virtual ~FlyNoWay() = default;
    FlyNoWay(const FlyNoWay&) = delete;
    FlyNoWay(FlyNoWay&&) = delete;
    FlyNoWay& operator=(const FlyNoWay&) = delete;
    FlyNoWay& operator=(FlyNoWay&&) = delete;

public:
    virtual void fly() const override;
};
