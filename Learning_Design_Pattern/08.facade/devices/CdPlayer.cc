#include "CdPlayer.h"
#include "Amplifier.h"
#include <iostream>

CdPlayer::CdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier)
    : _description(description)
    , _amplifier(amplifier)
{
}

CdPlayer::~CdPlayer() = default;

void CdPlayer::on() const { std::cout << _description << " on" << std::endl; }

void CdPlayer::off() const { std::cout << _description << " off" << std::endl; }

void CdPlayer::eject() const { std::cout << _description << " eject" << std::endl; }

void CdPlayer::play(std::string title)
{
    _title = title;
    std::cout << _description << " playing \"" << _title << "\"" << std::endl;
}

void CdPlayer::play(int track)
{
    if (_title.empty()) {
        std::cout << _description << " can't play track " << _currentTrack << ", no cd inserted" << std::endl;
    } else {
        _currentTrack = track;
        std::cout << _description << " playing track " << _currentTrack << std::endl;
    }
}

void CdPlayer::stop()
{
    _currentTrack = 0;
    std::cout << _description << " stopped" << std::endl;
}

void CdPlayer::pause() { std::cout << _description << " paused \"" << _title << "\"" << std::endl; }

std::string CdPlayer::toShow() const { return _description; }