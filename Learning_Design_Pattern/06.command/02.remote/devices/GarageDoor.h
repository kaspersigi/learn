#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class GarageDoor : public NonCopyable
{
public:
    explicit GarageDoor(const std::string location);
    ~GarageDoor() = default;

    void up() const;
    void down() const;
    void stop() const;
    void lighton() const;
    void lightoff() const;

private:
    std::string _location {};
};