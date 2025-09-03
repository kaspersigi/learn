#pragma once

#include <string>

class Veggies
{
public:
    virtual ~Veggies() = default;

    virtual std::string toShow() const = 0;

protected:
    Veggies() = default;
    Veggies(const Veggies&) = delete;
    Veggies(Veggies&&) = delete;
    Veggies& operator = (const Veggies&) = delete;
    Veggies& operator = (Veggies&&) = delete;
};