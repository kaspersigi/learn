#pragma once

#include "../interface/NonCopyable.h"
#include <memory>
#include <string>

class DvdPlayer;

class Projector : public NonCopyable
{
public:
    Projector(std::string description, std::shared_ptr<DvdPlayer> dvdPlayer);
    ~Projector();

    void on() const;
    void off() const;
    void wideScreenMode();
    void tvMode();
    std::string toShow() const;

private:
    std::string _description;
    std::weak_ptr<DvdPlayer> _dvdPlayer;
};