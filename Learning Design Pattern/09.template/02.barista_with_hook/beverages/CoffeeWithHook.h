#pragma once

#include "../interface/CaffeineBeverageWithHook.h"

class CoffeeWithHook : public CaffeineBeverageWithHook {
public:
    CoffeeWithHook() = default;
    ~CoffeeWithHook() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;
    virtual bool customerWantsCondiments() const override;
    char getUserInput() const;

protected:
    CoffeeWithHook(const CoffeeWithHook&) = delete;
    CoffeeWithHook(CoffeeWithHook&&) = delete;
    CoffeeWithHook& operator=(const CoffeeWithHook&) = delete;
    CoffeeWithHook& operator=(CoffeeWithHook&&) = delete;
};