#pragma once

#include <iostream>

class IObject
{
public:
    virtual ~IObject();

protected:
    IObject();
    IObject(const IObject&) = delete;
    IObject(IObject&&) = delete;
    IObject& operator = (const IObject&) = delete;
    IObject& operator = (IObject&&) = delete;

public:
    static IObject* Instance();
    virtual void show() const;

private:
    std::string _name = std::string("IObject");
};