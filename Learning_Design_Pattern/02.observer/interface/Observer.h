#pragma once

#include "NonCopyable.h"

class Observer : public NonCopyable
{
public:
    virtual ~Observer() = default;

    virtual void update(float temperature, float humidity, float pressure) = 0;

protected:
    Observer() = default;
};