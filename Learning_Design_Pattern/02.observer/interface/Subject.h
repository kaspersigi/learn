#pragma once

#include "NonCopyable.h"

class Observer;

class Subject : public NonCopyable
{
public:
    virtual ~Subject() = default;

    virtual void registerObserver(Observer * observer) = 0;
    virtual void removeObserver(Observer * observer) = 0;
    virtual void notifyObservers() const = 0;

protected:
    Subject() = default;
};