#pragma once

#include "../../interface/Veggies.h"

class RedPepper : public Veggies {
public:
    RedPepper() = default;
    virtual ~RedPepper() = default;

    virtual std::string toShow() const override;
};