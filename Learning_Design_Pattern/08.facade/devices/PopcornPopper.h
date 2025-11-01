#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class PopcornPopper : public NonCopyable {
public:
    explicit PopcornPopper(std::string description);
    ~PopcornPopper() = default;

    void on() const;
    void off() const;
    void pop() const;
    std::string toShow() const;

private:
    std::string _description {};
};