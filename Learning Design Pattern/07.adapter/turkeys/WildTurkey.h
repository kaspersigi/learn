#pragma once

#include "../interface/Turkey.h"

class WildTurkey : public Turkey {
public:
    WildTurkey();
    virtual ~WildTurkey() = default;

protected:
    WildTurkey(const WildTurkey&) = delete;
    WildTurkey(WildTurkey&&) = delete;
    WildTurkey& operator=(const WildTurkey&) = delete;
    WildTurkey& operator=(WildTurkey&&) = delete;

public:
    virtual void display() const override;
};