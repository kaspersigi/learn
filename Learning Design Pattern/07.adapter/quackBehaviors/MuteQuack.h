#pragma once

#include "../interface/QuackBehavior.h"

class MuteQuack : public QuackBehavior {
public:
    MuteQuack() = default;

protected:
    virtual ~MuteQuack() = default;
    MuteQuack(const MuteQuack&) = delete;
    MuteQuack(MuteQuack&&) = delete;
    MuteQuack& operator=(const MuteQuack&) = delete;
    MuteQuack& operator=(MuteQuack&&) = delete;

public:
    virtual void quack() const override;
};
