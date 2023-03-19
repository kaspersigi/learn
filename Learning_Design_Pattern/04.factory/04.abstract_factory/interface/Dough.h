#pragma once

#include <string>

class Dough {
public:
    virtual ~Dough() = default;

    virtual std::string toShow() const = 0;

protected:
    Dough() = default;
    Dough(const Dough&) = delete;
    Dough(Dough&&) = delete;
    Dough& operator=(const Dough&) = delete;
    Dough& operator=(Dough&&) = delete;
};