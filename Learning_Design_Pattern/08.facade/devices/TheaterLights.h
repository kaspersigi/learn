#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class TheaterLights : public NonCopyable
{
public:
    explicit TheaterLights(std::string description);
    ~TheaterLights() = default;

    void on() const;
    void off() const;
    void dim(int level);
    std::string toShow() const;

private:
    std::string _description {};
};