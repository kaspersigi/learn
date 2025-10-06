#pragma once

#include "../interface/NonCopyable.h"

class GarageDoor : public NonCopyable
{
public:
    GarageDoor() = default;
    ~GarageDoor() = default;

    void up() const;
    void down() const;
    void stop() const;
    void lighton() const;
    void lightoff() const;
};