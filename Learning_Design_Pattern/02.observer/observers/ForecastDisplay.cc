#include "ForecastDisplay.h"
#include <cassert>
#include <iostream>

ForecastDisplay::ForecastDisplay(Subject* weatherData)
    : _weatherData(weatherData)
{
    assert(weatherData);
    weatherData->registerObserver(this);
}

ForecastDisplay::~ForecastDisplay() { _weatherData->removeObserver(this); }

void ForecastDisplay::update(float temperature, float humidity, float pressure)
{
    _lastPressure = _currentPressure;
    _currentPressure = pressure;
    display();
}

void ForecastDisplay::display() const
{
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(3);
    std::cout << "Forecast: ";
    if (_currentPressure > _lastPressure) {
        std::cout << "Improving weather on the way!";
    } else if (_currentPressure == _lastPressure) {
        std::cout << "More of the same";
    } else if (_currentPressure < _lastPressure) {
        std::cout << "Watch out for cooler, rainy weather";
    }
    std::cout << std::endl;
}