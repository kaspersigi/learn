#pragma once

#include "NonCopyable.h"

class CaffeineBeverage : public NonCopyable
{
public:
    CaffeineBeverage() = default;

    virtual ~CaffeineBeverage() = default;

    virtual void prepareRecipe();

    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;

private:
    void boilWater() const;
    void pourInCup() const;
};
