#include "DvdPlayer.h"
#include "Amplifier.h"
#include <iostream>

DvdPlayer::DvdPlayer(std::string description, const std::shared_ptr<Amplifier>& amplifier)
    : _description(std::move(description))
    , _amplifier(amplifier)
{
}

DvdPlayer::~DvdPlayer() = default;

void DvdPlayer::on() const { std::cout << _description << " on" << std::endl; }

void DvdPlayer::off() const { std::cout << _description << " off" << std::endl; }

void DvdPlayer::eject() const { std::cout << _description << " eject" << std::endl; }

void DvdPlayer::play(std::string movie)
{
    _movie = std::move(movie);
    std::cout << _description << " playing \"" << _movie << "\"" << std::endl;
}

void DvdPlayer::play(int track)
{
    if (_movie.empty()) {
        std::cout << _description << " can't play track " << track << " no dvd inserted" << std::endl;
    } else {
        _currentTrack = track;
        std::cout << _description << " playing track " << track << " of \"" << _movie << "\"" << std::endl;
    }
}

void DvdPlayer::stop()
{
    _currentTrack = 0;
    std::cout << _description << " stopped \"" << _movie << "\"" << std::endl;
}

void DvdPlayer::pause() { std::cout << _description << " paused \"" << _movie << "\"" << std::endl; }

std::string DvdPlayer::toShow() const { return _description; }

void DvdPlayer::setTwoChannelAudio() { std::cout << _description << " set two channel audio" << std::endl; }

void DvdPlayer::setSurroundAudio() { std::cout << _description << " set surround audio" << std::endl; }