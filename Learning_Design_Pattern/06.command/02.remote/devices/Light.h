#pragma once

#include <string>

class Light {
public:
    explicit Light(const std::string location);
    ~Light() = default;

    void on() const;
    void off() const;

protected:
    Light(const Light&) = delete;
    Light(Light&&) = delete;
    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;

private:
    std::string _location {};
};