#pragma once

#include <string>

class Sauce
{
public:
    virtual ~Sauce() = default;

    virtual std::string toShow() const = 0;

protected:
    Sauce() = default;
    Sauce(const Sauce&) = delete;
    Sauce(Sauce&&) = delete;
    Sauce& operator = (const Sauce&) = delete;
    Sauce& operator = (Sauce&&) = delete;
};