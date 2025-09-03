#pragma once

#include "../interface/QuackBehavior.h"

class FakeQuack : public QuackBehavior
{
public:
    FakeQuack() = default;

    virtual void quack() const override;

protected:
    virtual ~FakeQuack() = default;
    FakeQuack(const FakeQuack&) = delete;
    FakeQuack(FakeQuack&&) = delete;
    FakeQuack& operator = (const FakeQuack&) = delete;
    FakeQuack& operator = (FakeQuack&&) = delete;
};
