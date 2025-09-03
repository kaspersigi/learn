#pragma once

#include "../interface/Duck.h"
#include "../interface/Turkey.h"
#include <memory>

class TurkeyAdapter : public Duck
{
public:
    explicit TurkeyAdapter(const Turkey* turkey);
    explicit TurkeyAdapter(std::nullptr_t) = delete;
    virtual ~TurkeyAdapter() = default;

    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const override;

protected:
    TurkeyAdapter(const TurkeyAdapter&) = delete;
    TurkeyAdapter(TurkeyAdapter&&) = delete;
    TurkeyAdapter& operator = (const TurkeyAdapter&) = delete;
    TurkeyAdapter& operator = (TurkeyAdapter&&) = delete;

private:
    std::shared_ptr<const Turkey> _turkey {};
};