#pragma once

#include "../../interface/Clams.h"
#include <string>

class FreshClams : public Clams
{
public:
    FreshClams() = default;
    virtual ~FreshClams() = default;

    virtual std::string toShow() const override;

protected:
    FreshClams(const FreshClams&) = delete;
    FreshClams(FreshClams&&) = delete;
    FreshClams& operator = (const FreshClams&) = delete;
    FreshClams& operator = (FreshClams&&) = delete;
};