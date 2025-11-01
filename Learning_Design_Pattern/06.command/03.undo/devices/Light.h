#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class Light : public NonCopyable {
public:
    explicit Light(const std::string& location);
    ~Light() = default;

    void on() const;
    void off() const;
    void dim(int level) const;
    int getLevel() const;

private:
    std::string _location {};
    mutable int _level { 0 };
};