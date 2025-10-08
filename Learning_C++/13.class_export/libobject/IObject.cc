#include "IObject.h"
#include <iostream>

IObject::IObject() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

IObject::~IObject() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; };

void IObject::show() const { std::cout << _name << std::endl; }