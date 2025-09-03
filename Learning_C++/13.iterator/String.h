#include "Iterator.hpp"
#include <cstddef>
#include <ostream>

class String
{
public:
    String();
    explicit String(std::nullptr_t) = delete;
    explicit String(const char* c_str);
    String(const String& str);
    String(String && str);
    String& operator = (const String& str);
    String& operator = (String && str);
    ~String();

    friend std::ostream& operator << (std::ostream & os, const String& str);
    const char* c_str() const;
    std::size_t length() const;

    typedef Iterator<char> iterator;
    iterator begin();
    iterator end();

private:
    char* _c_str { nullptr };
    std::size_t _length { 0 };
    int count(const char* c_str) const;
};