#pragma once

class NonCopyable {
public:
    virtual ~NonCopyable() = default;

protected:
    NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
};