#pragma once

#include "../interface/Subject.h"
#include <list>

class WeatherData : public Subject
{
public:
    WeatherData() = default;
    virtual ~WeatherData() = default;

    virtual void registerObserver(Observer * observer) override;
    virtual void removeObserver(Observer * observer) override;
    virtual void notifyObservers() const override;
    void measurementsChanged();
    void setMeasurements(float temperature, float humidity, float pressure);
    float getTemperature() const;
    float getHumidity() const;
    float getPressure() const;

private:
    std::list<Observer*> _observers {};
    float _temperature {};
    float _humidity {};
    float _pressure {};
};