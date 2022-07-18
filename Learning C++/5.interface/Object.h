#pragma once

#include "IObject.h"

class Object : public IObject {
public:
    Object();

protected:
    virtual ~Object();
    Object(const Object&) = delete;
    Object(IObject&&) = delete;
    Object& operator=(const Object&) = delete;
    Object& operator=(Object&&) = delete;

public:
    virtual void show() const override;
    void deleter();

private:
    std::string _name = std::string("Object");
};