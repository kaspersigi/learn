#pragma once

#include "../interface/NonCopyable.h"
#include <string>

class Stereo : public NonCopyable
{
public:
    explicit Stereo(const std::string location);
    ~Stereo() = default;

    void on() const;
    void off() const;
    void setCD() const;
    void setDVD() const;
    void setRadio() const;
    void setVolume(int volume) const;

private:
    std::string _location {};
};