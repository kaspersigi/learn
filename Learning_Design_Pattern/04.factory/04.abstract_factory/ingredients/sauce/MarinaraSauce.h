#pragma once

#include "../../interface/Sauce.h"
#include <string>

class MarinaraSauce : public Sauce
{
public:
    MarinaraSauce() = default;
    virtual ~MarinaraSauce() = default;

    virtual std::string toShow() const override;

protected:
    MarinaraSauce(const MarinaraSauce&) = delete;
    MarinaraSauce(MarinaraSauce&&) = delete;
    MarinaraSauce& operator = (const MarinaraSauce&) = delete;
    MarinaraSauce& operator = (MarinaraSauce&&) = delete;
};