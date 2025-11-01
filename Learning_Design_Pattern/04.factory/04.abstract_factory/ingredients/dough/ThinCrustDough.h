#pragma once

#include "../../interface/Dough.h"
#include <string>

class ThinCrustDough : public Dough {
public:
    ThinCrustDough() = default;
    virtual ~ThinCrustDough() = default;

    virtual std::string toShow() const override;
};