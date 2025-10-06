#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class Hottub : public NonCopyable
{
public:
    Hottub() = default;
    ~Hottub() = default;

    enum State { OFF,
        ON };

    void on() const;
    void off() const;
    void bubblesOn() const;
    void bubblesOff() const;
    void jetsOn() const;
    void jetsOff() const;
    void setTemperature(int temperature);
    void heat() const;
    void cool() const;

private:
    mutable State _state { State::OFF };
    mutable int _temperature { 0 };
};