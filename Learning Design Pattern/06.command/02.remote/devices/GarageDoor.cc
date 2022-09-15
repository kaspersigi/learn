#include "GarageDoor.h"
#include <iostream>

GarageDoor::GarageDoor(const std::string location)
    : _location(location)
{
}

void GarageDoor::up() const { std::cout << _location << " garage Door is Open" << std::endl; }

void GarageDoor::down() const { std::cout << _location << " garage Door is Closed" << std::endl; }

void GarageDoor::stop() const { std::cout << _location << " garage Door is Stopped" << std::endl; }

void GarageDoor::lighton() const { std::cout << _location << " garage light is on" << std::endl; }

void GarageDoor::lightoff() const { std::cout << _location << " garage light is off" << std::endl; }