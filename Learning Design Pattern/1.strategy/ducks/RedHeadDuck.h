#pragma once

#include "../interface/Duck.h"

class RedHeadDuck : public Duck {
public:
    RedHeadDuck();
    virtual ~RedHeadDuck() = default;

protected:
    RedHeadDuck(const RedHeadDuck&) = delete;
    RedHeadDuck(RedHeadDuck&&) = delete;
    RedHeadDuck& operator=(const RedHeadDuck&) = delete;
    RedHeadDuck& operator=(RedHeadDuck&&) = delete;

public:
    virtual void display() const override;
};