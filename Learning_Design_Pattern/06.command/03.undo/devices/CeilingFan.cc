#include "CeilingFan.h"
#include <iostream>

CeilingFan::CeilingFan(const std::string& location)
    : _location(location)
{
}

void CeilingFan::low() const
{
    _level = Level::LOW;
    std::cout << _location << " ceiling fan is on low" << std::endl;
}

void CeilingFan::medium() const
{
    _level = Level::MEDIUM;
    std::cout << _location << " ceiling fan is on medium" << std::endl;
}

void CeilingFan::high() const
{
    _level = Level::HIGH;
    std::cout << _location << " ceiling fan is on high" << std::endl;
}

void CeilingFan::off() const
{
    _level = Level::DOWN;
    std::cout << _location << " ceiling fan is off" << std::endl;
}

CeilingFan::Level CeilingFan::getSpeed() { return _level; }