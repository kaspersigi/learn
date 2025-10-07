#pragma once

#include "../interface/NonCopyable.h"
#include <memory>
#include <string>

class Tuner;
class DvdPlayer;
class CdPlayer;

class Amplifier : public NonCopyable
{
public:
    explicit Amplifier(std::string description);
    ~Amplifier();

    void on() const;
    void off() const;
    void setStereoSound();
    void setSurroundSound();
    void setVolume(int level);
    void setTuner(std::shared_ptr<Tuner> tuner);
    void setDvd(std::shared_ptr<DvdPlayer> dvd);
    void setCd(std::shared_ptr<CdPlayer> cd);
    std::string toShow() const;

private:
    std::string _description;
    std::weak_ptr<Tuner> _tuner;
    std::weak_ptr<DvdPlayer> _dvd;
    std::weak_ptr<CdPlayer> _cd;
};