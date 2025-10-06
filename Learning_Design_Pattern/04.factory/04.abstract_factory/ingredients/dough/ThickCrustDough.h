#pragma once

#include "../../interface/Dough.h"
#include <string>

class ThickCrustDough : public Dough
{
public:
    ThickCrustDough() = default;
    virtual ~ThickCrustDough() = default;

    virtual std::string toShow() const override;
};