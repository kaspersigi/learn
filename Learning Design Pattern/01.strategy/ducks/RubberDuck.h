#pragma once

#include "../interface/Duck.h"

class RubberDuck : public Duck {
public:
    RubberDuck();
    virtual ~RubberDuck() = default;

    virtual void display() const override;

protected:
    RubberDuck(const RubberDuck&) = delete;
    RubberDuck(RubberDuck&&) = delete;
    RubberDuck& operator=(const RubberDuck&) = delete;
    RubberDuck& operator=(RubberDuck&&) = delete;
};