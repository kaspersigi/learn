#pragma once

#include "../interface/Duck.h"

class DecoyDuck : public Duck {
public:
    DecoyDuck();
    virtual ~DecoyDuck() = default;

    virtual void display() const override;

protected:
    DecoyDuck(const DecoyDuck&) = delete;
    DecoyDuck(DecoyDuck&&) = delete;
    DecoyDuck& operator=(const DecoyDuck&) = delete;
    DecoyDuck& operator=(DecoyDuck&&) = delete;
};