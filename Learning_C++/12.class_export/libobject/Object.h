#pragma once

#include "IObject.h"

class Object : public IObject
{
public:
    Object();
    virtual ~Object();

public:
    virtual void show() const override;

private:
    std::string _name = std::string("Object");
};