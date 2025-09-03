#pragma once

#include <memory>
#include <string>

class DvdPlayer;

class Projector
{
public:
    Projector(std::string description, std::shared_ptr<DvdPlayer> dvdPlayer);
    ~Projector() = default;

    void on() const;
    void off() const;
    void wideScreenMode();
    void tvMode();
    std::string toShow() const;

protected:
    Projector(const Projector&) = delete;
    Projector(Projector&&) = delete;
    Projector& operator = (const Projector&) = delete;
    Projector& operator = (Projector&&) = delete;

private:
    std::string _description {};
    std::weak_ptr<DvdPlayer> _dvdPlayer {};
};