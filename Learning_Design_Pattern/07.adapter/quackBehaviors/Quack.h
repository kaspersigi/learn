#pragma once

#include "../interface/QuackBehavior.h"

class Quack : public QuackBehavior
{
public:
    Quack() = default;

    virtual void quack() const override;

protected:
    virtual ~Quack() = default;
    Quack(const Quack&) = delete;
    Quack(Quack&&) = delete;
    Quack& operator = (const Quack&) = delete;
    Quack& operator = (Quack&&) = delete;
};
