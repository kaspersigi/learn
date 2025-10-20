#include "Light.h"
#include <cassert>
#include <iostream>

Light::Light(const std::string& location)
    : _location(location)
{
}

void Light::on() const
{
    _level = 100;
    std::cout << _location << " light is on" << std::endl;
}

void Light::off() const
{
    _level = 0;
    std::cout << _location << " light is off" << std::endl;
}

void Light::dim(int level) const
{
    assert(level >= 0 && level <= 100);
    _level = level;
    if (0 == _level) {
        this->off();
    } else {
        std::cout << _location << " light is dimmed to " << _level << "%" << std::endl;
    }
}

int Light::getLevel() const { return _level; }