#pragma once

class Light {
public:
    Light() = default;
    ~Light() = default;

    void on() const;
    void off() const;

protected:
    Light(const Light&) = delete;
    Light(Light&&) = delete;
    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;
};