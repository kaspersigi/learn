#include "IObject.h"
#include "Object.h"

IObject::IObject() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

IObject::~IObject() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; };

IObject* IObject::Instance() { return new Object(); }

void IObject::destroy() { delete this; }

void IObject::show() const { std::cout << _name << std::endl; }

extern "C" {
IObject* getInstance()
{
    return IObject::Instance();
}
}