#pragma once

#include <memory>

class FlyBehavior;
class QuackBehavior;

class Duck
{
public:
    virtual ~Duck() = default;

    void setFlyBehavior(FlyBehavior * flyBehavior);
    void setQuackBehavior(QuackBehavior * quackBehavior);
    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const = 0;

protected:
    Duck(FlyBehavior * flyBehavior, QuackBehavior * quackBehavior);
    Duck(const Duck&) = delete;
    Duck(Duck&&) = delete;
    Duck& operator = (const Duck&) = delete;
    Duck& operator = (Duck&&) = delete;

private:
    std::shared_ptr<FlyBehavior> _flyBehavior {};
    std::shared_ptr<QuackBehavior> _quackBehavior {};
};