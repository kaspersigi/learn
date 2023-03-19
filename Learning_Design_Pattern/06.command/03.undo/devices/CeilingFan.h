#pragma once

#include <string>

class CeilingFan {
public:
    explicit CeilingFan(const std::string location);
    ~CeilingFan() = default;

    enum Level { DOWN,
        LOW,
        MEDIUM,
        HIGH };

    void low() const;
    void medium() const;
    void high() const;
    void off() const;
    Level getSpeed();

protected:
    CeilingFan(const CeilingFan&) = delete;
    CeilingFan(CeilingFan&&) = delete;
    CeilingFan& operator=(const CeilingFan&) = delete;
    CeilingFan& operator=(CeilingFan&&) = delete;

private:
    std::string _location {};
    mutable Level _level { Level::DOWN };
};