#pragma once

#include "../interface/NonCopyable.h"
#include <memory>
#include <string>

class Amplifier;

class CdPlayer : public NonCopyable
{
public:
    CdPlayer(std::string description, const std::shared_ptr<Amplifier>& amplifier);
    ~CdPlayer();

    void on() const;
    void off() const;
    void eject() const;
    void play(std::string title);
    void play(int track);
    void stop();
    void pause();
    std::string toShow() const;

private:
    std::string _description;
    std::weak_ptr<Amplifier> _amplifier;
    std::string _title;
    int _currentTrack;
};