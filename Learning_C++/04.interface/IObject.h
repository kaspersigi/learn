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

private:
    std::string _name { "IObject" };
};