#include "IObject.h"
#include "Object.h"

IObject::IObject() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

IObject::~IObject() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; };

IObject* IObject::Instance() { return new Object(); }

void IObject::destroy() { delete this; }

void IObject::show() const { std::cout << _name << std::endl; }

extern "C" {
static IObject* _io = nullptr;

int initIObject()
{
    _io = new Object();
    if (_io)
        return 0;
    else
        return -1;
}

void destroyIObject()
{
    delete _io;
    _io = nullptr;
}

void show()
{
    _io->show();
}
}