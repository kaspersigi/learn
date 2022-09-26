#pragma once

#include "../../interface/Clams.h"
#include <string>

class FrozenClams : public Clams {
public:
    FrozenClams() = default;
    virtual ~FrozenClams() = default;

    virtual std::string toShow() const override;

protected:
    FrozenClams(const FrozenClams&) = delete;
    FrozenClams(FrozenClams&&) = delete;
    FrozenClams& operator=(const FrozenClams&) = delete;
    FrozenClams& operator=(FrozenClams&&) = delete;
};