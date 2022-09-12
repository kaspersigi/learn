#pragma once

#include <string>

class Clams {
public:
    virtual ~Clams() = default;
    virtual std::string toShow() const = 0;

protected:
    Clams() = default;
    Clams(const Clams&) = delete;
    Clams(Clams&&) = delete;
    Clams& operator=(const Clams&) = delete;
    Clams& operator=(Clams&&) = delete;
};