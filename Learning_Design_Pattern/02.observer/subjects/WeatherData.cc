#include "WeatherData.h"
#include "../interface/Observer.h"
#include <algorithm>

void WeatherData::registerObserver(Observer* observer)
{
    _observers.push_back(observer);
}

void WeatherData::removeObserver(Observer* observer)
{
    _observers.remove(observer);
}

void WeatherData::notifyObservers() const
{
    std::for_each(_observers.begin(), _observers.end(), [&](auto e) { e->update(_temperature, _humidity, _pressure); });
}

void WeatherData::measurementsChanged() { notifyObservers(); }

void WeatherData::setMeasurements(float temperature, float humidity, float pressure)
{
    _temperature = temperature;
    _humidity = humidity;
    _pressure = pressure;
    measurementsChanged();
}

float WeatherData::getTemperature() const { return _temperature; }

float WeatherData::getHumidity() const { return _humidity; }

float WeatherData::getPressure() const { return _pressure; }