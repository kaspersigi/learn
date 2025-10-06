#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class CheesePizza : public Pizza
{
public:
    explicit CheesePizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit CheesePizza(std::nullptr_t) = delete;
    virtual ~CheesePizza() = default;

    void prepare();

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};