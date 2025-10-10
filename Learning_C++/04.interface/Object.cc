#include "Object.h"
#include <iostream>

Object::Object() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

Object::~Object() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; }

void Object::show() const { std::cout << __PRETTY_FUNCTION__ << " " << _name << std::endl; }

void Object::print() const { std::cout << __PRETTY_FUNCTION__ << " Object" << std::endl; }