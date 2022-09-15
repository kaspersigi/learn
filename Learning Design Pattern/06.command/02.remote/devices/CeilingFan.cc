#include "CeilingFan.h"
#include <iostream>

CeilingFan::Level CeilingFan::level = Level::LOW;

CeilingFan::CeilingFan(const std::string location)
    : _location(location)
{
}

void CeilingFan::on() const
{
    std::cout << _location << " CeilingFan is on" << std::endl;
}

void CeilingFan::off() const { std::cout << _location << " CeilingFan is off" << std::endl; }