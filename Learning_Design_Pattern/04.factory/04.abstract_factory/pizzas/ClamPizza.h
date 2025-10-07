#pragma once

#include "../interface/Pizza.h"
#include <memory>

class PizzaIngredientFactory;

class ClamPizza : public Pizza
{
public:
    explicit ClamPizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit ClamPizza(std::nullptr_t) = delete;
    ~ClamPizza() override;

    void prepare() override;

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};