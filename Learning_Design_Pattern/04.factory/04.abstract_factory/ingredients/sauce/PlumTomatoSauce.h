#pragma once

#include "../../interface/Sauce.h"
#include <string>

class PlumTomatoSauce : public Sauce
{
public:
    PlumTomatoSauce() = default;
    virtual ~PlumTomatoSauce() = default;

    virtual std::string toShow() const override;

protected:
    PlumTomatoSauce(const PlumTomatoSauce&) = delete;
    PlumTomatoSauce(PlumTomatoSauce&&) = delete;
    PlumTomatoSauce& operator = (const PlumTomatoSauce&) = delete;
    PlumTomatoSauce& operator = (PlumTomatoSauce&&) = delete;
};