#pragma once

#include <string>

class PopcornPopper
{
public:
    explicit PopcornPopper(std::string description);
    ~PopcornPopper() = default;

    void on() const;
    void off() const;
    void pop() const;
    std::string toShow() const;

protected:
    PopcornPopper(const PopcornPopper&) = delete;
    PopcornPopper(PopcornPopper&&) = delete;
    PopcornPopper& operator = (const PopcornPopper&) = delete;
    PopcornPopper& operator = (PopcornPopper&&) = delete;

private:
    std::string _description {};
};