#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class CeilingFan : public NonCopyable {
public:
    explicit CeilingFan(const std::string& location);
    virtual ~CeilingFan() = default;

    enum class Level : std::uint8_t {
        DOWN,
        LOW,
        MEDIUM,
        HIGH,
    };

    void low() const;
    void medium() const;
    void high() const;
    void off() const;
    Level getSpeed();

private:
    std::string _location {};
    mutable Level _level { Level::DOWN };
};