#pragma once

#include "../interface/CaffeineBeverageWithHook.h"

class TeaWithHook : public CaffeineBeverageWithHook {
public:
    TeaWithHook() = default;
    ~TeaWithHook() = default;

    virtual void brew() const override;
    virtual void addCondiments() const override;
    virtual bool customerWantsCondiments() const override;
    char getUserInput() const;

protected:
    TeaWithHook(const TeaWithHook&) = delete;
    TeaWithHook(TeaWithHook&&) = delete;
    TeaWithHook& operator=(const TeaWithHook&) = delete;
    TeaWithHook& operator=(TeaWithHook&&) = delete;
};