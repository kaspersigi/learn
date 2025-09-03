#pragma once

#include <string>

class GarageDoor
{
public:
    explicit GarageDoor(const std::string location);
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

private:
    std::string _location {};
};