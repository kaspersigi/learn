#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"

class CurrentConditionsDisplay : public Observer, public DisplayElement
{
public:
    explicit CurrentConditionsDisplay(Subject * weatherData);
    virtual ~CurrentConditionsDisplay();

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

protected:
    CurrentConditionsDisplay(const CurrentConditionsDisplay&) = delete;
    CurrentConditionsDisplay(CurrentConditionsDisplay&&) = delete;
    CurrentConditionsDisplay& operator = (const CurrentConditionsDisplay&) = delete;
    CurrentConditionsDisplay& operator = (CurrentConditionsDisplay&&) = delete;

private:
    Subject* _weatherData {};
    float _temperature {};
    float _humidity {};
};