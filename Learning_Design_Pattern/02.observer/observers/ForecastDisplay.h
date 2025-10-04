#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"
#include <memory>

class ForecastDisplay : public Observer, public DisplayElement
{
public:
    explicit ForecastDisplay(std::shared_ptr<Subject> weatherData);

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    std::weak_ptr<Subject> _weatherData;
    float _currentPressure { 29.92F };
    float _lastPressure {};
};