#include <iostream>

template <typename T>
class Object {
public:
    Object(T t);
    void show();

private:
    T _t;
};

template <typename T>
Object<T>::Object(T t)
    : _t(t)
{
}

template <typename T>
void Object<T>::show() { std::cout << _t << std::endl; }

auto main(int argc, char* argv[]) -> int
{
    Object<int> obj(3);
    obj.show();
    return 0;
}