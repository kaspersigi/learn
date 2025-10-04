#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"
#include <memory>

class HeatIndexDisplay : public Observer, public DisplayElement
{
public:
    explicit HeatIndexDisplay(std::shared_ptr<Subject> weatherData);

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    std::weak_ptr<Subject> _weatherData;
    float _heatIndex {};
    float computeHeatIndex(float t, float rh) const;
};