#pragma once

#include "NonCopyable.h"
#include <string>

class Clams : public NonCopyable {
public:
    virtual ~Clams() = default;

    virtual std::string toShow() const = 0;

protected:
    Clams() = default;
};