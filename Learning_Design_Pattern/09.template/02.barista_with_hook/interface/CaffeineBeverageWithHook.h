#pragma once

#include "NonCopyable.h"

class CaffeineBeverageWithHook : public NonCopyable {
public:
    CaffeineBeverageWithHook() = default;

    virtual void prepareRecipe();

public:
    virtual ~CaffeineBeverageWithHook() = default;

    virtual void brew() const = 0;
    virtual void addCondiments() const = 0;
    virtual bool customerWantsCondiments() const;

private:
    void boilWater() const;
    void pourInCup() const;
};
