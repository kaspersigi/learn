#include <iostream>
#include <memory>

class IInner {
public:
    IInner();
    ~IInner();

protected:
    IInner(const IInner&) = delete;
    IInner(IInner&&) = delete;
    IInner& operator=(const IInner&) = delete;
    IInner& operator=(IInner&&) = delete;
};

IInner::IInner() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

IInner::~IInner() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; }

class Inner {
public:
    Inner();
    ~Inner();
};

Inner::Inner() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

Inner::~Inner() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; }

class IObject {
public:
    virtual ~IObject();

protected:
    IObject();
    IObject(const IObject&) = delete;
    IObject(IObject&&) = delete;
    IObject& operator=(const IObject&) = delete;
    IObject& operator=(IObject&&) = delete;

public:
    static IObject* Instance();
    void destroy();
    virtual void show() const;

private:
    std::string _name = std::string("IObject");
    IInner iinner;
};

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

private:
    std::string _name = std::string("Object");
    Inner inner;
};

IObject::IObject() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

IObject::~IObject() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; };

IObject* IObject::Instance() { return new Object(); }

void IObject::destroy() { delete this; }

void IObject::show() const { std::cout << _name << std::endl; }

Object::Object() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

Object::~Object() { std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl; }

void Object::show() const { std::cout << _name << std::endl; }

auto main(int argc, char* argv[]) -> int
{
    IObject* p_io1 = IObject::Instance();
    p_io1->show();
    p_io1->destroy();
    std::cout << "--------------------" << std::endl;
    std::shared_ptr<IObject> p_io2 { IObject::Instance() };
    p_io2->show();
    std::cout << "--------------------" << std::endl;

    return 0;
}

#if 0
IInner::IInner()构造函数
IObject::IObject()构造函数
Inner::Inner()构造函数
Object::Object()构造函数
Object
virtual Object::~Object()析构函数
Inner::~Inner()析构函数
virtual IObject::~IObject()析构函数
IInner::~IInner()析构函数
--------------------
IInner::IInner()构造函数
IObject::IObject()构造函数
Inner::Inner()构造函数
Object::Object()构造函数
Object
--------------------
virtual Object::~Object()析构函数
Inner::~Inner()析构函数
virtual IObject::~IObject()析构函数
IInner::~IInner()析构函数
#endif