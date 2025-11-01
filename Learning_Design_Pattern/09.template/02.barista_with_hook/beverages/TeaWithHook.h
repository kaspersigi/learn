#pragma once

#include "../interface/CaffeineBeverageWithHook.h"

class TeaWithHook : public CaffeineBeverageWithHook {
public:
    TeaWithHook() = default;
    virtual ~TeaWithHook() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;
    virtual bool customerWantsCondiments() const override;
    char getUserInput() const;
};