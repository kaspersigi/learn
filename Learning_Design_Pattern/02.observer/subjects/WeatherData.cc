#include "WeatherData.h"
#include "../interface/Observer.h"
#include <algorithm>

WeatherData::~WeatherData() = default;

void WeatherData::registerObserver(std::shared_ptr<Observer> observer)
{
    _observers.push_back(observer);
}

void WeatherData::removeObserver(const std::shared_ptr<Observer>& observer)
{
    // C++20 contains std::erase_if, which is simpler
    std::erase_if(_observers, [&](const std::weak_ptr<Observer>& o) {
        return o.expired() || o.lock() == observer;
    });
}

void WeatherData::notifyObservers()
{
    // C++20 contains std::erase_if, which is simpler
    std::erase_if(_observers, [](const std::weak_ptr<Observer>& o) {
        return o.expired();
    });

    // It's not safe to modify the container while iterating, so we create a copy
    // A better way is to use a mutable member and lock it, but for this example, copy is fine.
    auto observers_copy = _observers;
    for (const auto& weak_observer : observers_copy) {
        if (auto shared_observer = weak_observer.lock()) {
            shared_observer->update(_temperature, _humidity, _pressure);
        }
    }

    // A more advanced implementation could clean up expired observers here.
    // For example, by re-building the list of non-expired observers.
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