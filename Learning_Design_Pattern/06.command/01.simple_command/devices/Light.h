#pragma once

#include "../interface/NonCopyable.h"

class Light : public NonCopyable
{
public:
    Light() = default;
    ~Light() = default;

    void on() const;
    void off() const;
};