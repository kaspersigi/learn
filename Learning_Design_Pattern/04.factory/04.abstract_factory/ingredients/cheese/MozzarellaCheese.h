#pragma once

#include "../../interface/Cheese.h"
#include <string>

class MozzarellaCheese : public Cheese
{
public:
    MozzarellaCheese() = default;
    virtual ~MozzarellaCheese() = default;

    virtual std::string toShow() const override;

protected:
    MozzarellaCheese(const MozzarellaCheese&) = delete;
    MozzarellaCheese(MozzarellaCheese&&) = delete;
    MozzarellaCheese& operator = (const MozzarellaCheese&) = delete;
    MozzarellaCheese& operator = (MozzarellaCheese&&) = delete;
};