#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include <memory>

class Subject;

class ForecastDisplay : public Observer, public DisplayElement
{
public:
    explicit ForecastDisplay(std::shared_ptr<Subject> weatherData);
    ~ForecastDisplay() override;

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    std::weak_ptr<Subject> _weatherData;
    float _currentPressure { 29.92F };
    float _lastPressure {};
};