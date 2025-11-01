#pragma once

#include "../interface/Duck.h"
#include <memory>

class Turkey;

class TurkeyAdapter : public Duck {
public:
    explicit TurkeyAdapter(std::shared_ptr<const Turkey> turkey);
    explicit TurkeyAdapter(std::nullptr_t) = delete;
    virtual ~TurkeyAdapter();

    void performFly() const;
    void performQuack() const;
    void swim() const;
    virtual void display() const override;

private:
    std::shared_ptr<const Turkey> _turkey;
};