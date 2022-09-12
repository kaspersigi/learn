#pragma once

#include "../interface/Dough.h"
#include <string>

class ThinCrustDough : public Dough {
public:
    ThinCrustDough() = default;
    virtual ~ThinCrustDough() = default;
    virtual std::string toShow() const override;

protected:
    ThinCrustDough(const ThinCrustDough&) = delete;
    ThinCrustDough(ThinCrustDough&&) = delete;
    ThinCrustDough& operator=(const ThinCrustDough&) = delete;
    ThinCrustDough& operator=(ThinCrustDough&&) = delete;
};