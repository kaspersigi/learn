#pragma once

#include "../interface/QuackBehavior.h"

class Quack : public QuackBehavior {
public:
    Quack() = default;

protected:
    virtual ~Quack() = default;
    Quack(const Quack&) = delete;
    Quack(Quack&&) = delete;
    Quack& operator=(const Quack&) = delete;
    Quack& operator=(Quack&&) = delete;

public:
    virtual void quack() const override;
};
