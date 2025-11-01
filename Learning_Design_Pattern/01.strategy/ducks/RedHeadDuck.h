#pragma once

#include "../interface/Duck.h"

class RedHeadDuck : public Duck {
public:
    RedHeadDuck();
    virtual ~RedHeadDuck() = default;

    virtual void display() const override;
};