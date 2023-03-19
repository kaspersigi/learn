#include "Light.h"
#include <iostream>

void Light::on() const { std::cout << "Light is on" << std::endl; }

void Light::off() const { std::cout << "Light is off" << std::endl; }