#pragma once

#include "../interface/QuackBehavior.h"

class Squeak : public QuackBehavior {
public:
    Squeak() = default;

protected:
    virtual ~Squeak() = default;
    Squeak(const Squeak&) = delete;
    Squeak(Squeak&&) = delete;
    Squeak& operator=(const Squeak&) = delete;
    Squeak& operator=(Squeak&&) = delete;

public:
    virtual void quack() const override;
};
