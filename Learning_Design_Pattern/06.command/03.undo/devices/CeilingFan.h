#pragma once

#include "../interface/NonCopyable.h"
#include <string>
#include <sys/types.h>

class CeilingFan : public NonCopyable {
public:
    explicit CeilingFan(const std::string& location);
    ~CeilingFan() = default;

    enum class Level : u_int8_t {
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