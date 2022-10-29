#include <iostream>

class Object {
public:
    Object();
    // Object(const char* ptr, std::size_t length = 0);
    explicit Object(const char* ptr, std::size_t length = 0);
    Object(const Object& obj);
    Object(Object&& obj);
    Object& operator=(const Object& obj);
    Object& operator=(Object&& obj);
    ~Object();

private:
    char* _ptr {};
    std::size_t _length {};
};

Object::Object() { std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl; }

Object::Object(const char* ptr, std::size_t length)
{
    std::cout << __PRETTY_FUNCTION__ << "构造函数" << std::endl;
    if (nullptr != ptr) {
        _ptr = new char[length + 1];
        _length = length;
        for (int i = 0; i <= length; i++) {
            _ptr[i] = ptr[i];
        }
    }
}

Object::Object(const Object& obj)
{
    std::cout << __PRETTY_FUNCTION__ << "拷贝构造函数" << std::endl;
    if (nullptr != obj._ptr) {
        _ptr = new char[obj._length + 1];
        _length = obj._length;
        for (int i = 0; i <= obj._length; i++) {
            _ptr[i] = obj._ptr[i];
        }
    }
}

Object::Object(Object&& obj)
    : _ptr(obj._ptr)
    , _length(obj._length)
{
    std::cout << __PRETTY_FUNCTION__ << "移动构造函数" << std::endl;
    obj._ptr = nullptr;
    obj._length = 0;
}

Object& Object::operator=(const Object& obj)
{
    std::cout << __PRETTY_FUNCTION__ << "拷贝赋值运算符" << std::endl;
    if (this == &obj) // 自赋值检查
    {
        std::cout << "自赋值" << std::endl;
        return *this;
    }

    delete _ptr;
    _ptr = new char[obj._length + 1];
    _length = obj._length;
    for (int i = 0; i <= obj._length; i++) {
        _ptr[i] = obj._ptr[i];
    }
    return *this;
}

Object& Object::operator=(Object&& obj)
{
    std::cout << __PRETTY_FUNCTION__ << "移动赋值运算符" << std::endl;
    if (this == &obj) // 自赋值检查
    {
        std::cout << "自赋值" << std::endl;
        return *this;
    }

    _ptr = obj._ptr;
    _length = obj._length;
    obj._ptr = nullptr;
    obj._length = 0;
    return *this;
}

Object::~Object()
{
    std::cout << __PRETTY_FUNCTION__ << "析构函数" << std::endl;
    delete[] _ptr;
}

Object func(std::string& str)
{
    return Object(str.c_str(), str.length());
}

auto main(int argc, char* argv[]) -> int
{
    std::string str("Hello World");
    Object obj1 { str.c_str(), str.length() };
    std::cout << "--------------------" << std::endl;

    Object obj2 = obj1;
    std::cout << "--------------------" << std::endl;

    Object obj3 = func(str);
    std::cout << "--------------------" << std::endl;

    Object obj4;
    obj4 = obj1;
    // obj4 = obj4; // 自赋值
    std::cout << "--------------------" << std::endl;

    Object obj5;
    obj5 = func(str);
    std::cout << "--------------------" << std::endl;

    return 0;
}

#if 0
c++14
Object::Object(const char *, std::size_t)构造函数
--------------------
Object::Object(const Object &)拷贝构造函数
--------------------
Object::Object(const char *, std::size_t)构造函数
Object::Object(Object &&)移动构造函数
Object::~Object()析构函数
Object::Object(Object &&)移动构造函数
Object::~Object()析构函数
--------------------
Object::Object()构造函数
Object &Object::operator=(const Object &)拷贝赋值运算符
--------------------
Object::Object()构造函数
Object::Object(const char *, std::size_t)构造函数
Object::Object(Object &&)移动构造函数
Object::~Object()析构函数
Object &Object::operator=(Object &&)移动赋值运算符
Object::~Object()析构函数
--------------------
Object::~Object()析构函数
Object::~Object()析构函数
Object::~Object()析构函数
Object::~Object()析构函数
Object::~Object()析构函数

c++17
Object::Object(const char *, std::size_t)构造函数
--------------------
Object::Object(const Object &)拷贝构造函数
--------------------
Object::Object(const char *, std::size_t)构造函数
--------------------
Object::Object()构造函数
Object &Object::operator=(const Object &)拷贝赋值运算符
--------------------
Object::Object()构造函数
Object::Object(const char *, std::size_t)构造函数
Object &Object::operator=(Object &&)移动赋值运算符
Object::~Object()析构函数
--------------------
Object::~Object()析构函数
Object::~Object()析构函数
Object::~Object()析构函数
Object::~Object()析构函数
Object::~Object()析构函数
#endif