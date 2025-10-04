#include "StatisticsDisplay.h"
#include <iostream>

StatisticsDisplay::StatisticsDisplay(std::shared_ptr<Subject> weatherData)
    : _weatherData(weatherData)
{
}

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