#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"

class HeatIndexDisplay : public Observer, public DisplayElement
{
public:
    explicit HeatIndexDisplay(Subject * weatherData);
    virtual ~HeatIndexDisplay();

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    Subject* _weatherData {};
    float _heatIndex {};
    float computeHeatIndex(float t, float rh) const;
};