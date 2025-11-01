#pragma once

#include "NonCopyable.h"
#include <memory>

class Observer : public NonCopyable, public std::enable_shared_from_this<Observer> {
public:
    virtual ~Observer() = default;

    virtual void update(float temperature, float humidity, float pressure) = 0;

protected:
    Observer() = default;
};