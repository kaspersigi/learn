#pragma once

#include "../interface/QuackBehavior.h"

class Gobble : public QuackBehavior
{
public:
    Gobble() = default;
    virtual ~Gobble() = default;

    virtual void quack() const override;
};