#pragma once

#include "../interface/Duck.h"
#include "../interface/Turkey.h"
#include <memory>

class TurkeyAdapter : public Duck
{
public:
    explicit TurkeyAdapter(std::shared_ptr<const Turkey> turkey);
    explicit TurkeyAdapter(std::nullptr_t) = delete;
    virtual ~TurkeyAdapter() = default;

    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const override;

private:
    std::shared_ptr<const Turkey> _turkey {};
};