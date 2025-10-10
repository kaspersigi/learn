#pragma once

#include "Interface.h"
#include <string>

class IObject : public Interface
{
public:
    virtual ~IObject();

protected:
    IObject();

public:
    virtual void show() const;
    void print() const;

private:
    std::string _name { "IObject" };
};