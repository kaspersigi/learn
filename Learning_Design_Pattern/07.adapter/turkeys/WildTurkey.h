#pragma once

#include "../interface/Turkey.h"

class WildTurkey : public Turkey
{
public:
    WildTurkey();
    virtual ~WildTurkey() = default;

    virtual void display() const override;
};