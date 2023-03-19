#include "Hottub.h"
#include <cassert>
#include <iostream>

void Hottub::on() const { _state = State::ON; }

void Hottub::off() const { _state = State::OFF; }

void Hottub::bubblesOn() const
{
    if (State::ON == _state)
        std::cout << "Hottub is bubbling!" << std::endl;
}

void Hottub::bubblesOff() const
{
    if (State::OFF == _state)
        std::cout << "Hottub is not bubbling" << std::endl;
}

void Hottub::jetsOn() const
{
    if (State::ON == _state)
        std::cout << "Hottub jets are on" << std::endl;
}

void Hottub::jetsOff() const
{
    if (State::OFF == _state)
        std::cout << "Hottub jets are off" << std::endl;
}

void Hottub::setTemperature(int temperature)
{
    assert(temperature >= 0);
    _temperature = temperature;
}

void Hottub::heat() const
{
    _temperature = 105;
    std::cout << "Hottub is heating to a steaming 105 degrees" << std::endl;
}

void Hottub::cool() const
{
    _temperature = 98;
    std::cout << "Hottub is cooling to 98 degrees" << std::endl;
}