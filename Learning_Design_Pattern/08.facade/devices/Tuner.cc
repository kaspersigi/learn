#include "Tuner.h"
#include "Amplifier.h"
#include <iostream>

Tuner::Tuner(std::string description, std::shared_ptr<Amplifier> amplifier)
    : _description(description)
    , _amplifier(amplifier)
{
}

Tuner::~Tuner() = default;

void Tuner::on() const { std::cout << _description << " on" << std::endl; }

void Tuner::off() const { std::cout << _description << " off" << std::endl; }

void Tuner::setFrequency(double frequency)
{
    _frequency = frequency;
    std::cout << _description << " setting frequency to " << _frequency << std::endl;
}

void Tuner::setAm() { std::cout << _description << " setting AM mode" << std::endl; }

void Tuner::setFm() { std::cout << _description << " setting FM mode" << std::endl; }

std::string Tuner::toShow() const { return _description; }