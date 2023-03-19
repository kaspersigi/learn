#include "Projector.h"
#include <iostream>

Projector::Projector(std::string description, std::shared_ptr<DvdPlayer> dvdPlayer)
    : _description(description)
    , _dvdPlayer(dvdPlayer)
{
}

void Projector::on() const { std::cout << _description << " on" << std::endl; }

void Projector::off() const { std::cout << _description << " off" << std::endl; }

void Projector::wideScreenMode() { std::cout << _description << " in widescreen mode (16x9 aspect ratio)" << std::endl; }

void Projector::tvMode() { std::cout << _description << " in tv mode (4x3 aspect ratio)" << std::endl; }

std::string Projector::toShow() const { return _description; }