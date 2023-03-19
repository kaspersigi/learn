#pragma once

#include <memory>

class FlyBehavior;
class QuackBehavior;

class Turkey {
public:
    virtual ~Turkey() = default;

    void setFlyBehavior(FlyBehavior* flyBehavior);
    void setQuackBehavior(QuackBehavior* quackBehavior);
    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const = 0;

protected:
    Turkey(FlyBehavior* flyBehavior, QuackBehavior* quackBehavior);
    Turkey(const Turkey&) = delete;
    Turkey(Turkey&&) = delete;
    Turkey& operator=(const Turkey&) = delete;
    Turkey& operator=(Turkey&&) = delete;

private:
    std::shared_ptr<FlyBehavior> _flyBehavior {};
    std::shared_ptr<QuackBehavior> _quackBehavior {};
};