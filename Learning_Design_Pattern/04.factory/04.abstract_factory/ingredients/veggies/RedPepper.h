#pragma once

#include "../../interface/Veggies.h"

class RedPepper : public Veggies
{
public:
    RedPepper() = default;
    virtual ~RedPepper() = default;

    virtual std::string toShow() const override;

protected:
    RedPepper(const RedPepper&) = delete;
    RedPepper(RedPepper&&) = delete;
    RedPepper& operator = (const RedPepper&) = delete;
    RedPepper& operator = (RedPepper&&) = delete;
};