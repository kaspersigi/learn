#pragma once

#include <string>

class Pepperoni {
public:
    virtual ~Pepperoni() = default;

    virtual std::string toShow() const = 0;

protected:
    Pepperoni() = default;
    Pepperoni(const Pepperoni&) = delete;
    Pepperoni(Pepperoni&&) = delete;
    Pepperoni& operator=(const Pepperoni&) = delete;
    Pepperoni& operator=(Pepperoni&&) = delete;
};