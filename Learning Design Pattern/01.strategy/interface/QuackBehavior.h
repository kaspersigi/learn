#pragma once

class QuackBehavior {
public:
    virtual ~QuackBehavior() = default;

    virtual void quack() const = 0;

protected:
    QuackBehavior() = default;
    QuackBehavior(const QuackBehavior&) = delete;
    QuackBehavior(QuackBehavior&&) = delete;
    QuackBehavior& operator=(const QuackBehavior&) = delete;
    QuackBehavior& operator=(QuackBehavior&&) = delete;
};