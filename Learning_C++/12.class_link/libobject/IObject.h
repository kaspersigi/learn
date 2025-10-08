#pragma once

#include "Interface.h"
#include <memory>
#include <string>

class IObject : public Interface
{
protected:
    IObject();
    virtual ~IObject();

public:
    __attribute__((visibility("default"))) static std::shared_ptr<IObject> createInstance();
    virtual void show() const;

private:
    std::string _name { "IObject" };
};