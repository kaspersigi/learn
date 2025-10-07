#include "String.h"
#include <cassert>

int String::count(const char* c_str) const
{
    assert(c_str);
    int i = 0;
    while ('\0' != c_str[i])
        ++i;
    return i;
}

String::String()
{
    _c_str = new char[1];
    _c_str[0] = '\0';
}

String::String(const char* c_str)
{
    _length = count(c_str);
    _c_str = new char[_length + 1];
    for (int i = 0; i < _length; ++i) {
        _c_str[i] = c_str[i];
    }
    _c_str[_length] = '\0';
}

String::String(const String& str)
{
    _length = str._length;
    _c_str = new char[_length + 1];
    for (int i = 0; i < _length; ++i) {
        _c_str[i] = str._c_str[i];
    }
    _c_str[_length] = '\0';
}

String::String(String&& str) noexcept
    : _c_str(str._c_str)
    , _length(str._length)
{
    str._c_str = nullptr;
    str._length = 0;
}

String& String::operator=(const String& str)
{
    if (this != &str) {
        String temp(str);
        std::swap(_c_str, temp._c_str);
        std::swap(_length, temp._length);
    }
    return *this;
}

String& String::operator=(String&& str) noexcept
{
    if (this != &str) {
        delete[] _c_str;
        _c_str = str._c_str;
        _length = str._length;
        str._c_str = nullptr;
        str._length = 0;
    }
    return *this;
}

String::~String()
{
    delete[] _c_str;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    os << str._c_str;
    return os;
}

const char* String::c_str() const { return _c_str; }

std::size_t String::length() const { return _length; }

String::iterator String::begin() { return iterator(_c_str); }

String::iterator String::end() { return iterator(_c_str + _length); }