#pragma once

#include "../../interface/Cheese.h"
#include <string>

class MozzarellaCheese : public Cheese
{
public:
    MozzarellaCheese() = default;
    virtual ~MozzarellaCheese() = default;

    virtual std::string toShow() const override;
};