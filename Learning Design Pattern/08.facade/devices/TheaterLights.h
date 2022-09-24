#pragma once

#include <string>

class TheaterLights {
public:
    explicit TheaterLights(std::string description);
    ~TheaterLights() = default;

    void on() const;
    void off() const;
    void dim(int level);
    std::string toShow() const;

protected:
    TheaterLights(const TheaterLights&) = delete;
    TheaterLights(TheaterLights&&) = delete;
    TheaterLights& operator=(const TheaterLights&) = delete;
    TheaterLights& operator=(TheaterLights&&) = delete;

private:
    std::string _description {};
};