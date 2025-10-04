#pragma once

#include "../interface/DisplayElement.h"
#include "../interface/Observer.h"
#include "../interface/Subject.h"
#include <memory>

class CurrentConditionsDisplay : public Observer, public DisplayElement
{
public:
    explicit CurrentConditionsDisplay(std::shared_ptr<Subject> weatherData);

    virtual void update(float temperature, float humidity, float pressure) override;
    virtual void display() const override;

private:
    std::weak_ptr<Subject> _weatherData;
    float _temperature {};
    float _humidity {};
};