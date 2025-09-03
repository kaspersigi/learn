#pragma once

#include <string>

class Cheese
{
public:
    virtual ~Cheese() = default;

    virtual std::string toShow() const = 0;

protected:
    Cheese() = default;
    Cheese(const Cheese&) = delete;
    Cheese(Cheese&&) = delete;
    Cheese& operator = (const Cheese&) = delete;
    Cheese& operator = (Cheese&&) = delete;
};