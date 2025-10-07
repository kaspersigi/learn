#pragma once

#include "../interface/NonCopyable.h"
#include <memory>
#include <string>

class Amplifier;

class Tuner : public NonCopyable
{
public:
    Tuner(std::string description, std::shared_ptr<Amplifier> amplifier);
    ~Tuner();

    void on() const;
    void off() const;
    void setFrequency(double frequency);
    void setAm();
    void setFm();
    std::string toShow() const;

private:
    std::string _description;
    std::weak_ptr<Amplifier> _amplifier;
    double _frequency;
};