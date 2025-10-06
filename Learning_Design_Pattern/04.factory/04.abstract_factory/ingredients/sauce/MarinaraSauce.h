#pragma once

#include "../../interface/Sauce.h"
#include <string>

class MarinaraSauce : public Sauce
{
public:
    MarinaraSauce() = default;
    virtual ~MarinaraSauce() = default;

    virtual std::string toShow() const override;
};