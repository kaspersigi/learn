#pragma once

#include "../../interface/Cheese.h"
#include <string>

class ParmesanCheese : public Cheese
{
public:
    ParmesanCheese() = default;
    virtual ~ParmesanCheese() = default;

    virtual std::string toShow() const override;

protected:
    ParmesanCheese(const ParmesanCheese&) = delete;
    ParmesanCheese(ParmesanCheese&&) = delete;
    ParmesanCheese& operator = (const ParmesanCheese&) = delete;
    ParmesanCheese& operator = (ParmesanCheese&&) = delete;
};