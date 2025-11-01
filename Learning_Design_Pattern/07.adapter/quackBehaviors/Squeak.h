#pragma once

#include "../interface/QuackBehavior.h"

class Squeak : public QuackBehavior {
public:
    Squeak() = default;
    virtual ~Squeak() = default;

    virtual void quack() const override;
};