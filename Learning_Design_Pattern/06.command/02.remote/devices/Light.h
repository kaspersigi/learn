#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class Light : public NonCopyable {
public:
    explicit Light(const std::string& location);
    virtual ~Light() = default;

    void on() const;
    void off() const;

private:
    std::string _location {};
};