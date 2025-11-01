#pragma once

#include "../../interface/Clams.h"
#include <string>

class FreshClams : public Clams {
public:
    FreshClams() = default;
    virtual ~FreshClams() = default;

    virtual std::string toShow() const override;
};