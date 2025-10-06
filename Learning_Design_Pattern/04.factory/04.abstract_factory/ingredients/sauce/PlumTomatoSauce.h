#pragma once

#include "../../interface/Sauce.h"
#include <string>

class PlumTomatoSauce : public Sauce
{
public:
    PlumTomatoSauce() = default;
    virtual ~PlumTomatoSauce() = default;

    virtual std::string toShow() const override;
};