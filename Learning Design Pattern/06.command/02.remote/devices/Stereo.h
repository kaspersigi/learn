#pragma once

#include <string>

class Stereo {
public:
    explicit Stereo(const std::string location);
    ~Stereo() = default;

    void on() const;
    void off() const;
    void setCD() const;
    void setDVD() const;
    void setRadio() const;
    void setVolume(int volume) const;

protected:
    Stereo(const Stereo&) = delete;
    Stereo(Stereo&&) = delete;
    Stereo& operator=(const Stereo&) = delete;
    Stereo& operator=(Stereo&&) = delete;

private:
    std::string _location {};
};