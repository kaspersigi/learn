#pragma once

#include "../interface/QuackBehavior.h"

class Squeak : public QuackBehavior
{
public:
    Squeak() = default;

    virtual void quack() const override;

protected:
    virtual ~Squeak() = default;
    Squeak(const Squeak&) = delete;
    Squeak(Squeak&&) = delete;
    Squeak& operator = (const Squeak&) = delete;
    Squeak& operator = (Squeak&&) = delete;
};
