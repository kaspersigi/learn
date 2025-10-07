#pragma once

#include "../interface/Pizza.h"
#include <memory>

class PizzaIngredientFactory;

class CheesePizza : public Pizza
{
public:
    explicit CheesePizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit CheesePizza(std::nullptr_t) = delete;
    ~CheesePizza() override;

    void prepare() override;

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};