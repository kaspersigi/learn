#include "IObject.h"
#include "Object.h"
#include <iostream>
#include <memory>

std::shared_ptr<IObject> IObject::createInstance()
{
    return std::make_shared<Object>();
}

IObject::IObject() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

IObject::~IObject() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; };

void IObject::show() const { std::cout << _name << std::endl; }