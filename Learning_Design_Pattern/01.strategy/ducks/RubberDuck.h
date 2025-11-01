#pragma once

#include "../interface/Duck.h"

class RubberDuck : public Duck {
public:
    RubberDuck();
    virtual ~RubberDuck() = default;

    virtual void display() const override;
};