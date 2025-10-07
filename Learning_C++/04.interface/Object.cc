#include "Object.h"
#include <iostream>

Object::Object() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

Object::~Object() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; }

void Object::show() const { std::cout << _name << std::endl; }