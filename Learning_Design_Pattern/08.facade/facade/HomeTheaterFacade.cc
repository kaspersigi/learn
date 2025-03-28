#include "HomeTheaterFacade.h"
#include "../devices/devices.h"
#include <iostream>

HomeTheaterFacade::HomeTheaterFacade(std::shared_ptr<Amplifier> amp, std::shared_ptr<Tuner> tuner, std::shared_ptr<DvdPlayer> dvd, std::shared_ptr<CdPlayer> cd, std::shared_ptr<Projector> projector, std::shared_ptr<TheaterLights> lights, std::shared_ptr<Screen> screen, std::shared_ptr<PopcornPopper> popper)
    : _amp(amp)
    , _tuner(tuner)
    , _dvd(dvd)
    , _cd(cd)
    , _projector(projector)
    , _lights(lights)
    , _screen(screen)
    , _popper(popper)
{
}

void HomeTheaterFacade::watchMovie(std::string movie)
{
    if (_popper.use_count() && _lights.use_count() && _screen.use_count() && _projector.use_count() && _amp.use_count() && _dvd.use_count()) {
        std::cout << "Get ready to watch a movie..." << std::endl;
        _popper.lock()->on();
        _popper.lock()->pop();
        _lights.lock()->dim(10);
        _screen.lock()->down();
        _projector.lock()->on();
        _projector.lock()->wideScreenMode();
        _amp.lock()->on();
        _amp.lock()->setDvd(_dvd.lock());
        _amp.lock()->setSurroundSound();
        _amp.lock()->setVolume(5);
        _dvd.lock()->on();
        _dvd.lock()->play(movie);
    }
}

void HomeTheaterFacade::endMovie()
{
    if (_popper.use_count() && _lights.use_count() && _screen.use_count() && _projector.use_count() && _amp.use_count() && _dvd.use_count()) {
        std::cout << "Shutting movie theater down..." << std::endl;
        _popper.lock()->off();
        _lights.lock()->on();
        _screen.lock()->up();
        _projector.lock()->off();
        _amp.lock()->off();
        _dvd.lock()->stop();
        _dvd.lock()->eject();
        _dvd.lock()->off();
    }
}

void HomeTheaterFacade::listenToCd(std::string cdTitle)
{
    if (_lights.use_count() && _amp.use_count() && _cd.use_count()) {
        std::cout << "Get ready for an audiopile experence..." << std::endl;
        _lights.lock()->on();
        _amp.lock()->on();
        _amp.lock()->setVolume(5);
        _amp.lock()->setCd(_cd.lock());
        _amp.lock()->setStereoSound();
        _cd.lock()->on();
        _cd.lock()->play(cdTitle);
    }
}

void HomeTheaterFacade::endCd()
{
    if (_amp.use_count() && _cd.use_count()) {
        std::cout << "Shutting down CD..." << std::endl;
        _amp.lock()->off();
        _amp.lock()->setCd(_cd.lock());
        _cd.lock()->eject();
        _cd.lock()->off();
    }
}

void HomeTheaterFacade::listenToRadio(double frequency)
{
    if (_tuner.use_count() && _amp.use_count()) {
        std::cout << "Tuning in the airwaves..." << std::endl;
        _tuner.lock()->on();
        _tuner.lock()->setFrequency(frequency);
        _amp.lock()->on();
        _amp.lock()->setVolume(5);
        _amp.lock()->setTuner(_tuner.lock());
    }
}

void HomeTheaterFacade::endRadio()
{
    if (_tuner.use_count() && _amp.use_count()) {
        std::cout << "Shutting down the tuner..." << std::endl;
        _tuner.lock()->off();
        _amp.lock()->off();
    }
}