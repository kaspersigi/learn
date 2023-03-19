#include "IObject.h"
#include "Object.h"
#include <iostream>
#include <memory>

auto main(int argc, char* argv[]) -> int
{
    IObject* p_io1 = IObject::Instance();
    p_io1->show();
    p_io1->destroy();
    std::cout << "--------------------" << std::endl;
    std::shared_ptr<IObject> p_io2 { IObject::Instance() };
    p_io2->show();
    std::cout << "--------------------" << std::endl;
    Object* p_o1 = new Object();
    p_o1->show();
    p_o1->deleter();
    std::cout << "--------------------" << std::endl;
    std::shared_ptr<Object> p_o2 { new Object(), [](auto e) { e->deleter(); } };
    p_o2->show();
    std::cout << "--------------------" << std::endl;

    return 0;
}

#if 0
IObject::IObject()构造函数
Object::Object()构造函数
Object
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
--------------------
IObject::IObject()构造函数
Object::Object()构造函数
Object
--------------------
IObject::IObject()构造函数
Object::Object()构造函数
Object
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
--------------------
IObject::IObject()构造函数
Object::Object()构造函数
Object
--------------------
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
#endif