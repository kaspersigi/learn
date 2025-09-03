#pragma once

class FlyBehavior
{
public:
    virtual ~FlyBehavior() = default;

    virtual void fly() const = 0;

protected:
    FlyBehavior() = default;
    FlyBehavior(const FlyBehavior&) = delete;
    FlyBehavior(FlyBehavior&&) = delete;
    FlyBehavior& operator = (const FlyBehavior&) = delete;
    FlyBehavior& operator = (FlyBehavior&&) = delete;
};