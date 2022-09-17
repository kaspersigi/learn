#pragma once

#include "../interface/Duck.h"

class ModelDuck : public Duck {
public:
    ModelDuck();
    virtual ~ModelDuck() = default;

protected:
    ModelDuck(const ModelDuck&) = delete;
    ModelDuck(ModelDuck&&) = delete;
    ModelDuck& operator=(const ModelDuck&) = delete;
    ModelDuck& operator=(ModelDuck&&) = delete;

public:
    virtual void display() const override;
};