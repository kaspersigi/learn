#include "Stereo.h"
#include <cassert>
#include <iostream>

Stereo::Stereo(const std::string& location)
    : _location(location)
{
}

void Stereo::on() const
{
    std::cout << _location << " stereo is on" << std::endl;
}

void Stereo::off() const { std::cout << _location << " stereo is off" << std::endl; }

void Stereo::setCD() const { std::cout << _location << " stereo is set for CD input" << std::endl; }

void Stereo::setDVD() const { std::cout << _location << " stereo is set for DVD input" << std::endl; }

void Stereo::setRadio() const { std::cout << _location << " stereo is set for Radio" << std::endl; }

void Stereo::setVolume(int volume) const
{
    assert(volume > 0 && volume < 12);
    std::cout << _location << " Stereo volume set to " << volume << std::endl;
}