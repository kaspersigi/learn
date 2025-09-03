#pragma once

#include <memory>
#include <string>

class Amplifier;

class CdPlayer
{
public:
    CdPlayer(std::string description, std::shared_ptr<Amplifier> amplifier);
    ~CdPlayer() = default;

    void on() const;
    void off() const;
    void eject() const;
    void play(std::string title);
    void play(int track);
    void stop();
    void pause();
    std::string toShow() const;

protected:
    CdPlayer(const CdPlayer&) = delete;
    CdPlayer(CdPlayer&&) = delete;
    CdPlayer& operator = (const CdPlayer&) = delete;
    CdPlayer& operator = (CdPlayer&&) = delete;

private:
    std::string _description {};
    std::weak_ptr<Amplifier> _amplifier {};
    std::string _title {};
    int _currentTrack {};
};