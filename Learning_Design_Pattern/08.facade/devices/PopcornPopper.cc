#include "PopcornPopper.h"
#include <iostream>

PopcornPopper::PopcornPopper(std::string description)
    : _description(description)
{
}

void PopcornPopper::on() const { std::cout << _description << " on" << std::endl; }

void PopcornPopper::off() const { std::cout << _description << " off" << std::endl; }

void PopcornPopper::pop() const { std::cout << _description << " popping popcorn!" << std::endl; }

std::string PopcornPopper::toShow() const { return _description; }