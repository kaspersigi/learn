#pragma once

#include "../interface/QuackBehavior.h"

class Quack : public QuackBehavior {
public:
    Quack() = default;
    virtual ~Quack() = default;

    virtual void quack() const override;
};