#pragma once

#include "../interface/QuackBehavior.h"

class FakeQuack : public QuackBehavior
{
public:
    FakeQuack() = default;
    virtual ~FakeQuack() = default;

    virtual void quack() const override;
};