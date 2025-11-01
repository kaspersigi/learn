#pragma once

#include "../interface/CaffeineBeverageWithHook.h"

class CoffeeWithHook : public CaffeineBeverageWithHook {
public:
    CoffeeWithHook() = default;
    virtual ~CoffeeWithHook() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;
    virtual bool customerWantsCondiments() const override;
    char getUserInput() const;
};