#include "StatisticsDisplay.h"
#include <cassert>
#include <iostream>

StatisticsDisplay::StatisticsDisplay(Subject* weatherData)
    : _weatherData(weatherData)
{
    assert(weatherData);
    _weatherData->registerObserver(this);
}

StatisticsDisplay::~StatisticsDisplay() { _weatherData->removeObserver(this); }

void StatisticsDisplay::update(float temperature, float humidity, float pressure)
{
    _tempSum += temperature;
    _numReadings++;

    if (temperature > _maxTemp) {
        _maxTemp = temperature;
    }

    if (temperature < _minTemp) {
        _minTemp = temperature;
    }

    display();
}

void StatisticsDisplay::display() const
{
    std::cout.setf(std::ios::showpoint);
    std::cout.precision(3);
    std::cout << "Avg/Max/Min temperature = " << (_tempSum / _numReadings);
    std::cout << "/" << _maxTemp << "/" << _minTemp << std::endl;
}