#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class Screen : public NonCopyable {
public:
    explicit Screen(std::string description);
    ~Screen() = default;

    void up() const;
    void down() const;
    std::string toShow() const;

private:
    std::string _description {};
};