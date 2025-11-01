#pragma once

#include "../interface/Duck.h"

class MallardDuck : public Duck {
public:
    MallardDuck();
    virtual ~MallardDuck() = default;

    virtual void display() const override;
};