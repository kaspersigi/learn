#include "StatisticsDisplay.h"
#include "../interface/Subject.h"
#include <iostream>

StatisticsDisplay::StatisticsDisplay(const std::shared_ptr<Subject>& weatherData)
    : _weatherData(weatherData)
{
}

StatisticsDisplay::~StatisticsDisplay() = default;

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
    std::cout << "Avg/Max/Min temperature = " << _tempSum / static_cast<float>(_numReadings);
    std::cout << "/" << _maxTemp << "/" << _minTemp << std::endl;
}