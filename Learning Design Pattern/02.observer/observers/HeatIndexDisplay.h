#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"

class HeatIndexDisplay : public Observer, public DisplayElement {
public:
    explicit HeatIndexDisplay(Subject* weatherData);
    virtual ~HeatIndexDisplay();

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

protected:
    HeatIndexDisplay(const HeatIndexDisplay&) = delete;
    HeatIndexDisplay(HeatIndexDisplay&&) = delete;
    HeatIndexDisplay& operator=(const HeatIndexDisplay&) = delete;
    HeatIndexDisplay& operator=(HeatIndexDisplay&&) = delete;

private:
    Subject* _weatherData {};
    float _heatIndex {};
    float computeHeatIndex(float t, float rh) const;
};