#include "Light.h"
#include <iostream>

Light::Light(const std::string& location)
    : _location(location)
{
}

void Light::on() const
{
    std::cout << _location << " light is on" << std::endl;
}

void Light::off() const { std::cout << _location << " light is off" << std::endl; }