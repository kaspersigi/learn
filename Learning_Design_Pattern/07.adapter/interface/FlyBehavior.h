#pragma once

#include "NonCopyable.h"

class FlyBehavior : public NonCopyable
{
public:
    virtual ~FlyBehavior() = default;

    virtual void fly() const = 0;

protected:
    FlyBehavior() = default;
};