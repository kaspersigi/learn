#pragma once

#include "../interface/Duck.h"

class MallardDuck : public Duck {
public:
    MallardDuck();
    virtual ~MallardDuck() = default;

    virtual void display() const override;

protected:
    MallardDuck(const MallardDuck&) = delete;
    MallardDuck(MallardDuck&&) = delete;
    MallardDuck& operator=(const MallardDuck&) = delete;
    MallardDuck& operator=(MallardDuck&&) = delete;
};