#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include <memory>

class Subject;

class HeatIndexDisplay : public Observer, public DisplayElement
{
public:
    explicit HeatIndexDisplay(const std::shared_ptr<Subject>& weatherData);
    ~HeatIndexDisplay() override;

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    std::weak_ptr<Subject> _weatherData;
    float _heatIndex {};
    float computeHeatIndex(float t, float rh) const;
};