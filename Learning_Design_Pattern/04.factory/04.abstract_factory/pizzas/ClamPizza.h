#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class ClamPizza : public Pizza
{
public:
    explicit ClamPizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit ClamPizza(std::nullptr_t) = delete;
    virtual ~ClamPizza() = default;

    void prepare() const;

protected:
    ClamPizza(const ClamPizza&) = delete;
    ClamPizza(ClamPizza&&) = delete;
    ClamPizza& operator = (const ClamPizza&) = delete;
    ClamPizza& operator = (ClamPizza&&) = delete;

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};