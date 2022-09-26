#pragma once

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

class HomeTheaterFacade {
public:
    HomeTheaterFacade(std::shared_ptr<Amplifier> amp, std::shared_ptr<Tuner> tuner, std::shared_ptr<DvdPlayer> dvd, std::shared_ptr<CdPlayer> cd, std::shared_ptr<Projector> projector, std::shared_ptr<TheaterLights> lights, std::shared_ptr<Screen> screen, std::shared_ptr<PopcornPopper> popper);
    ~HomeTheaterFacade() = default;

    void watchMovie(std::string movie);
    void endMovie();
    void listenToCd(std::string cdTitle);
    void endCd();
    void listenToRadio(double frequency);
    void endRadio();

protected:
    HomeTheaterFacade(const HomeTheaterFacade&) = delete;
    HomeTheaterFacade(HomeTheaterFacade&&) = delete;
    HomeTheaterFacade& operator=(const HomeTheaterFacade&) = delete;
    HomeTheaterFacade& operator=(HomeTheaterFacade&&) = delete;

private:
    std::weak_ptr<Amplifier> _amp {};
    std::weak_ptr<Tuner> _tuner {};
    std::weak_ptr<DvdPlayer> _dvd {};
    std::weak_ptr<CdPlayer> _cd {};
    std::weak_ptr<Projector> _projector {};
    std::weak_ptr<TheaterLights> _lights {};
    std::weak_ptr<Screen> _screen {};
    std::weak_ptr<PopcornPopper> _popper {};
};