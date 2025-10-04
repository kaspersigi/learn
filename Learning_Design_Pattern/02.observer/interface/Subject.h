#pragma once

#include "NonCopyable.h"
#include <memory>

class Observer;

class Subject : public NonCopyable
{
public:
    virtual ~Subject() = default;

    virtual void registerObserver(std::shared_ptr<Observer> observer) = 0;
    virtual void removeObserver(const std::shared_ptr<Observer>& observer) = 0;
    virtual void notifyObservers() = 0;

protected:
    Subject() = default;
};