#pragma once

#include "../interface/NonCopyable.h"
#include <memory>
#include <string>

class Amplifier;

class DvdPlayer : public NonCopyable
{
public:
    DvdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier);
    ~DvdPlayer() = default;

    void on() const;
    void off() const;
    void eject() const;
    void play(std::string movie);
    void play(int track);
    void stop();
    void pause();
    std::string toShow() const;
    void setTwoChannelAudio();
    void setSurroundAudio();

private:
    std::string _description {};
    std::weak_ptr<Amplifier> _amplifier {};
    std::string _movie {};
    int _currentTrack {};
};