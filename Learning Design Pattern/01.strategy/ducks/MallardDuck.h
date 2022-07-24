#pragma once

#include "../interface/Duck.h"

class MallardDuck : public Duck {
public:
    MallardDuck();
    virtual ~MallardDuck() = default;

protected:
    MallardDuck(const MallardDuck&) = delete;
    MallardDuck(MallardDuck&&) = delete;
    MallardDuck& operator=(const MallardDuck&) = delete;
    MallardDuck& operator=(MallardDuck&&) = delete;

public:
    virtual void display() const override;
};