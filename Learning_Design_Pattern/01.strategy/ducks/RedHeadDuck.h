#pragma once

#include "../interface/Duck.h"

class RedHeadDuck : public Duck
{
public:
    RedHeadDuck();
    virtual ~RedHeadDuck() = default;

    virtual void display() const override;

protected:
    RedHeadDuck(const RedHeadDuck&) = delete;
    RedHeadDuck(RedHeadDuck&&) = delete;
    RedHeadDuck& operator = (const RedHeadDuck&) = delete;
    RedHeadDuck& operator = (RedHeadDuck&&) = delete;
};