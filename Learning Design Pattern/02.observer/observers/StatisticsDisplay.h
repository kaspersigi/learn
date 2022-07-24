#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"

class StatisticsDisplay : public Observer, public DisplayElement {
public:
    explicit StatisticsDisplay(Subject* weatherData);
    virtual ~StatisticsDisplay();

protected:
    StatisticsDisplay(const StatisticsDisplay&) = delete;
    StatisticsDisplay(StatisticsDisplay&&) = delete;
    StatisticsDisplay& operator=(const StatisticsDisplay&) = delete;
    StatisticsDisplay& operator=(StatisticsDisplay&&) = delete;

public:
    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    Subject* _weatherData {};
    float _maxTemp { 200.0F };
    float _minTemp {};
    float _tempSum {};
    int _numReadings {};
};