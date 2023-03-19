#pragma once

#include <string>

class TV {
public:
    explicit TV(const std::string location);
    ~TV() = default;

    void on() const;
    void off() const;
    void setInputChannel();

protected:
    TV(const TV&) = delete;
    TV(TV&&) = delete;
    TV& operator=(const TV&) = delete;
    TV& operator=(TV&&) = delete;

private:
    std::string _location {};
    mutable int _channel { 0 };
};