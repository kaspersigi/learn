#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class TV : public NonCopyable
{
public:
    explicit TV(const std::string& location);
    virtual ~TV() = default;

    void on() const;
    void off() const;
    void setInputChannel();

private:
    std::string _location {};
    mutable int _channel { 0 };
};