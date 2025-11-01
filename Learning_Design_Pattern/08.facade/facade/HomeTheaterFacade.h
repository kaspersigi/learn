#pragma once

#include "../interface/NonCopyable.h"
#include <memory>
#include <string>

class Amplifier;
class Tuner;
class DvdPlayer;
class CdPlayer;
class Projector;
class TheaterLights;
class Screen;
class PopcornPopper;

class HomeTheaterFacade : public NonCopyable {
public:
    HomeTheaterFacade(const std::shared_ptr<Amplifier>& amp, const std::shared_ptr<Tuner>& tuner, const std::shared_ptr<DvdPlayer>& dvd, const std::shared_ptr<CdPlayer>& cd, const std::shared_ptr<Projector>& projector, const std::shared_ptr<TheaterLights>& lights, const std::shared_ptr<Screen>& screen, const std::shared_ptr<PopcornPopper>& popper);
    ~HomeTheaterFacade();

    void watchMovie(std::string movie);
    void endMovie();
    void listenToCd(std::string cdTitle);
    void endCd();
    void listenToRadio(double frequency);
    void endRadio();

private:
    std::weak_ptr<Amplifier> _amp;
    std::weak_ptr<Tuner> _tuner;
    std::weak_ptr<DvdPlayer> _dvd;
    std::weak_ptr<CdPlayer> _cd;
    std::weak_ptr<Projector> _projector;
    std::weak_ptr<TheaterLights> _lights;
    std::weak_ptr<Screen> _screen;
    std::weak_ptr<PopcornPopper> _popper;
};