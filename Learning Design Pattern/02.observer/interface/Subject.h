#pragma once

class Observer;

class Subject {
public:
    virtual ~Subject() = default;

protected:
    Subject() = default;
    Subject(const Subject&) = delete;
    Subject(Subject&&) = delete;
    Subject& operator=(const Subject&) = delete;
    Subject& operator=(Subject&&) = delete;

public:
    virtual void registerObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() const = 0;
};