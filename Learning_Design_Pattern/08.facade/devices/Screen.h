#pragma once

#include <string>

class Screen
{
public:
    explicit Screen(std::string description);
    ~Screen() = default;

    void up() const;
    void down() const;
    std::string toShow() const;

protected:
    Screen(const Screen&) = delete;
    Screen(Screen&&) = delete;
    Screen& operator = (const Screen&) = delete;
    Screen& operator = (Screen&&) = delete;

private:
    std::string _description {};
};