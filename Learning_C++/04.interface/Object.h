#pragma once

#include "IObject.h"

class Object : public IObject
{
public:
    Object();
    virtual ~Object();

public:
    void show() const override;
    void print() const;

private:
    std::string _name = { "Object" };
};