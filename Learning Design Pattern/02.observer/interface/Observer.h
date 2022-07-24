#pragma once

class Observer {
public:
    virtual ~Observer() = default;

protected:
    Observer() = default;
    Observer(const Observer&) = delete;
    Observer(Observer&&) = delete;
    Observer& operator=(const Observer&) = delete;
    Observer& operator=(Observer&&) = delete;

public:
    virtual void update(float temperature, float humidity, float pressure) = 0;
};