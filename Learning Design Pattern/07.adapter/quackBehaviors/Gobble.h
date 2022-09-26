#pragma once

#include "../interface/QuackBehavior.h"

class Gobble : public QuackBehavior {
public:
    Gobble() = default;

    virtual void quack() const override;

protected:
    virtual ~Gobble() = default;
    Gobble(const Gobble&) = delete;
    Gobble(Gobble&&) = delete;
    Gobble& operator=(const Gobble&) = delete;
    Gobble& operator=(Gobble&&) = delete;
};
