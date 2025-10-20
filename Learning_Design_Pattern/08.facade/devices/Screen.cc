#include "Screen.h"
#include <iostream>

Screen::Screen(std::string description)
    : _description(std::move(description))
{
}

void Screen::up() const { std::cout << _description << " going up" << std::endl; }

void Screen::down() const { std::cout << _description << " going down" << std::endl; }

std::string Screen::toShow() const { return _description; }