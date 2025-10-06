#pragma once

#include "Cheese.h"
#include "Clams.h"
#include "Dough.h"
#include "NonCopyable.h"
#include "Pepperoni.h"
#include "Sauce.h"
#include "Veggies.h"
#include <iostream>
#include <memory>
#include <vector>

class Pizza : public NonCopyable
{
public:
    virtual ~Pizza();

    virtual void prepare() = 0;
    virtual void bake() const;
    virtual void cut() const;
    virtual void box() const;
    std::string getName() const;
    void setName(std::string name);
    std::string toShow() const;

protected:
    Pizza() = default;

    std::unique_ptr<Cheese> _cheese {};
    std::unique_ptr<Clams> _clam {};
    std::unique_ptr<Dough> _dough {};
    std::unique_ptr<Pepperoni> _pepperoni {};
    std::unique_ptr<Sauce> _sauce {};
    std::vector<std::unique_ptr<Veggies>> _veggies {};

private:
    std::string _name {};
};