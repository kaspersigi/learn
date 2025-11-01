#pragma once

#include "../interface/NonCopyable.h"

class Light : public NonCopyable {
public:
    Light() = default;
    virtual ~Light() = default;

    void on() const;
    void off() const;
};