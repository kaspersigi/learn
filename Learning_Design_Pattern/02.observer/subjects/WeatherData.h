#pragma once

#include "../interface/Subject.h"
#include <memory>
#include <vector>

class WeatherData : public Subject
{
public:
    WeatherData() = default;
    virtual ~WeatherData() = default;

    virtual void registerObserver(std::shared_ptr<Observer> observer) override;
    virtual void removeObserver(const std::shared_ptr<Observer>& observer) override;
    virtual void notifyObservers() override;
    void measurementsChanged();
    void setMeasurements(float temperature, float humidity, float pressure);
    float getTemperature() const;
    float getHumidity() const;
    float getPressure() const;

private:
    std::vector<std::weak_ptr<Observer>> _observers {};
    float _temperature {};
    float _humidity {};
    float _pressure {};
};