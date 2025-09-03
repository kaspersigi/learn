#pragma once

class GarageDoor
{
public:
    GarageDoor() = default;
    ~GarageDoor() = default;

    void up() const;
    void down() const;
    void stop() const;
    void lighton() const;
    void lightoff() const;

protected:
    GarageDoor(const GarageDoor&) = delete;
    GarageDoor(GarageDoor&&) = delete;
    GarageDoor& operator = (const GarageDoor&) = delete;
    GarageDoor& operator = (GarageDoor&&) = delete;
};