#include "Interface.h"
#include <iostream>

Interface::Interface() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

Interface::~Interface() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; }