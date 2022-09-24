#include "TheaterLights.h"
#include <iostream>

TheaterLights::TheaterLights(std::string description)
    : _description(description)
{
}

void TheaterLights::on() const { std::cout << _description << " on" << std::endl; }

void TheaterLights::off() const { std::cout << _description << " off" << std::endl; }

void TheaterLights::dim(int level) { std::cout << _description << " dimming to " << level << "%" << std::endl; }

std::string TheaterLights::toShow() const { return _description; }