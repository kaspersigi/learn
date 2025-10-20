#include <iostream>
#include <memory>

class Object {
public:
    Object();
    explicit Object(const char* ptr, std::size_t length = 0);
    Object(const Object& obj);
    Object(Object&& obj) noexcept;
    Object& operator=(const Object& obj);
    Object& operator=(Object&& obj) & noexcept;
    ~Object();

    void show() const;

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

Object::Object(Object&& obj) noexcept
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

    Object temp(obj);
    std::swap(_ptr, temp._ptr);
    std::swap(_length, temp._length);
    return *this;
}

Object& Object::operator=(Object&& obj) & noexcept
{
    std::cout << __PRETTY_FUNCTION__ << "移动赋值运算符" << std::endl;
    if (this == &obj) // 自赋值检查
    {
        std::cout << "自赋值" << std::endl;
        return *this;
    }

    delete[] _ptr;
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

void Object::show() const
{
    for (int i = 0; i < _length; ++i)
        std::cout << _ptr[i];
    std::cout << std::endl;
}

auto main(int argc, char* argv[]) -> int
{
    std::string str("Hello World");

    std::cout << "--------------------" << std::endl;
    auto p_obj = std::make_shared<Object>(str.c_str(), str.length());
    p_obj->show();
    std::cout << "--------------------" << std::endl;

    std::weak_ptr<Object> w_obj1(p_obj);
    std::weak_ptr<Object> w_obj2(p_obj);

    if (w_obj1.use_count())
        w_obj1.lock()->show();
    std::cout << "--------------------" << std::endl;

    p_obj.reset();
    if (w_obj2.use_count())
        w_obj2.lock()->show();
    std::cout << "--------------------" << std::endl;

    return 0;
}