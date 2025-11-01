#pragma once

#include "../interface/Duck.h"

class DecoyDuck : public Duck {
public:
    DecoyDuck();
    virtual ~DecoyDuck() = default;

    virtual void display() const override;
};