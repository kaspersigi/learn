#pragma once

#include <memory>
#include <string>

class Amplifier;

class Tuner {
public:
    Tuner(std::string description, std::shared_ptr<Amplifier> amplifier);
    ~Tuner() = default;

    void on() const;
    void off() const;
    void setFrequency(double frequency);
    void setAm();
    void setFm();
    std::string toShow() const;

protected:
    Tuner(const Tuner&) = delete;
    Tuner(Tuner&&) = delete;
    Tuner& operator=(const Tuner&) = delete;
    Tuner& operator=(Tuner&&) = delete;

private:
    std::string _description {};
    std::weak_ptr<Amplifier> _amplifier {};
    double _frequency {};
};