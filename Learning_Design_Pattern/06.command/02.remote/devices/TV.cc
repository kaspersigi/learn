#include "TV.h"
#include <iostream>

TV::TV(const std::string location)
    : _location(location)
{
}

void TV::on() const
{
    std::cout << _location << " TV is on" << std::endl;
}

void TV::off() const { std::cout << _location << " TV is off" << std::endl; }

void TV::setInputChannel()
{
    _channel = 3;
    std::cout << _location << " channel is set for VCR" << std::endl;
}