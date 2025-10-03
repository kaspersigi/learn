#pragma once

#include "../interface/QuackBehavior.h"

class MuteQuack : public QuackBehavior
{
public:
    MuteQuack() = default;
    virtual ~MuteQuack() = default;

    virtual void quack() const override;
};
