#include "IObject.h"
#include "Object.h"
#include <memory>
#include <print>

auto main(int argc, char* argv[]) -> int
{
    std::println("--------------------");
    {
        IObject* p_io1 = new Object();
        p_io1->show();
        p_io1->print();
        delete p_io1;
        p_io1 = nullptr;
    }
    std::println("--------------------");
    {
        std::shared_ptr<IObject> p_io2 = std::make_shared<Object>();
        p_io2->show();
        p_io2->print();
    }
    std::println("--------------------");
    {
        std::unique_ptr<IObject> p_io3 = std::make_unique<Object>();
        p_io3->show();
        p_io3->print();
    }
    std::println("--------------------");
    {
        auto p_o1 = std::make_unique<Object>();
        p_o1->show();
        p_o1->print();
    }
    std::println("--------------------");

    return 0;
}

#if 0
--------------------
Interface::Interface()构造函数
IObject::IObject()构造函数
Object::Object()构造函数
virtual void Object::show() const Object
void IObject::print() const IObject
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
virtual Interface::~Interface()析构函数
--------------------
Interface::Interface()构造函数
IObject::IObject()构造函数
Object::Object()构造函数
virtual void Object::show() const Object
void IObject::print() const IObject
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
virtual Interface::~Interface()析构函数
--------------------
Interface::Interface()构造函数
IObject::IObject()构造函数
Object::Object()构造函数
virtual void Object::show() const Object
void IObject::print() const IObject
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
virtual Interface::~Interface()析构函数
--------------------
Interface::Interface()构造函数
IObject::IObject()构造函数
Object::Object()构造函数
virtual void Object::show() const Object
void Object::print() const Object
virtual Object::~Object()析构函数
virtual IObject::~IObject()析构函数
virtual Interface::~Interface()析构函数
--------------------
#endif