#include "Amplifier.h"
#include "CdPlayer.h"
#include "DvdPlayer.h"
#include "Tuner.h"
#include <iostream>

Amplifier::Amplifier(std::string description)
    : _description(description)
{
}

Amplifier::~Amplifier() = default;

void Amplifier::on() const { std::cout << _description << " on" << std::endl; }

void Amplifier::off() const { std::cout << _description << " off" << std::endl; }

void Amplifier::setStereoSound() { std::cout << _description << " stereo mode on" << std::endl; }

void Amplifier::setSurroundSound() { std::cout << _description << " surround sound on (5 speakers, 1 subwoofer)" << std::endl; }

void Amplifier::setVolume(int level) { std::cout << _description << " setting volume to " << level << std::endl; }

void Amplifier::setTuner(std::shared_ptr<Tuner> tuner)
{
    _tuner = tuner;
    if (_tuner.use_count())
        std::cout << _description << " setting tuner to " << _tuner.lock()->toShow() << std::endl;
}

void Amplifier::setDvd(std::shared_ptr<DvdPlayer> dvd)
{
    _dvd = dvd;
    if (_dvd.use_count())
        std::cout << _description << " setting DVD player to " << _dvd.lock()->toShow() << std::endl;
}

void Amplifier::setCd(std::shared_ptr<CdPlayer> cd)
{
    _cd = cd;
    if (_cd.use_count())
        std::cout << _description << " setting CD player to " << _cd.lock()->toShow() << std::endl;
}

std::string Amplifier::toShow() const { return _description; }