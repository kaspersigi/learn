#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"

class ForecastDisplay : public Observer, public DisplayElement {
public:
    explicit ForecastDisplay(Subject* weatherData);
    virtual ~ForecastDisplay();

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

protected:
    ForecastDisplay(const ForecastDisplay&) = delete;
    ForecastDisplay(ForecastDisplay&&) = delete;
    ForecastDisplay& operator=(const ForecastDisplay&) = delete;
    ForecastDisplay& operator=(ForecastDisplay&&) = delete;

private:
    Subject* _weatherData {};
    float _currentPressure { 29.92F };
    float _lastPressure {};
};