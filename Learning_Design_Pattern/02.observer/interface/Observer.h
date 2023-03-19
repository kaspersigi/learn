#pragma once

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(float temperature, float humidity, float pressure) = 0;

protected:
    Observer() = default;
    Observer(const Observer&) = delete;
    Observer(Observer&&) = delete;
    Observer& operator=(const Observer&) = delete;
    Observer& operator=(Observer&&) = delete;
};