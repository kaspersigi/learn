#pragma once

#include "../../interface/Cheese.h"
#include <string>

class ParmesanCheese : public Cheese
{
public:
    ParmesanCheese() = default;
    virtual ~ParmesanCheese() = default;

    virtual std::string toShow() const override;
};