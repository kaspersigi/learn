#include "GarageDoor.h"
#include <iostream>

void GarageDoor::up() const { std::cout << "Garage Door is Open" << std::endl; }

void GarageDoor::down() const { std::cout << "Garage Door is Closed" << std::endl; }

void GarageDoor::stop() const { std::cout << "Garage Door is Stopped" << std::endl; }

void GarageDoor::lighton() const { std::cout << "Garage light is on" << std::endl; }

void GarageDoor::lightoff() const { std::cout << "Garage light is off" << std::endl; }