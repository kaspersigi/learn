#pragma once

#include "../interface/Turkey.h"

class WildTurkey : public Turkey
{
public:
    WildTurkey();
    virtual ~WildTurkey() = default;

    virtual void display() const override;

protected:
    WildTurkey(const WildTurkey&) = delete;
    WildTurkey(WildTurkey&&) = delete;
    WildTurkey& operator = (const WildTurkey&) = delete;
    WildTurkey& operator = (WildTurkey&&) = delete;
};