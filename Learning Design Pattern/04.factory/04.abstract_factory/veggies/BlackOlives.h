#pragma once

#include "../interface/Veggies.h"

class BlackOlives : public Veggies {
public:
    BlackOlives() = default;
    virtual ~BlackOlives() = default;
    virtual std::string toShow() const override;

protected:
    BlackOlives(const BlackOlives&) = delete;
    BlackOlives(BlackOlives&&) = delete;
    BlackOlives& operator=(const BlackOlives&) = delete;
    BlackOlives& operator=(BlackOlives&&) = delete;
};