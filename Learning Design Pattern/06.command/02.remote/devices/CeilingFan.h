#pragma once

#include <string>

class CeilingFan {
public:
    explicit CeilingFan(const std::string location);
    ~CeilingFan() = default;
    
    enum Level { LOW,
        MEDIUM,
        HIGH };
    static Level level;

    void on() const;
    void off() const;

protected:
    CeilingFan(const CeilingFan&) = delete;
    CeilingFan(CeilingFan&&) = delete;
    CeilingFan& operator=(const CeilingFan&) = delete;
    CeilingFan& operator=(CeilingFan&&) = delete;

private:
    std::string _location {};
};