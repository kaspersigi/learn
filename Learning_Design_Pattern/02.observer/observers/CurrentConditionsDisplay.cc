#include "CurrentConditionsDisplay.h"
#include <cassert>
#include <iostream>

CurrentConditionsDisplay::CurrentConditionsDisplay(Subject* weatherData)
    : _weatherData(weatherData)
{
    assert(weatherData);
    _weatherData->registerObserver(this);
}

CurrentConditionsDisplay::~CurrentConditionsDisplay()
{
    _weatherData->removeObserver(this);
}

void CurrentConditionsDisplay::update(float temperature, float humidity, float pressure)
{
    _temperature = temperature;
    _humidity = humidity;
    display();
}

void CurrentConditionsDisplay::display() const
{
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(3);
    std::cout << "Current conditions: " << _temperature;
    std::cout << " F degrees and " << _humidity;
    std::cout << "% humidity" << std::endl;
}