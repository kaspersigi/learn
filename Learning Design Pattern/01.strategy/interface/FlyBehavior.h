#pragma once

class FlyBehavior {
public:
    virtual ~FlyBehavior() = default;

protected:
    FlyBehavior() = default;
    FlyBehavior(const FlyBehavior&) = delete;
    FlyBehavior(FlyBehavior&&) = delete;
    FlyBehavior& operator=(const FlyBehavior&) = delete;
    FlyBehavior& operator=(FlyBehavior&&) = delete;

public:
    virtual void fly() const = 0;
};