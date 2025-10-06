#pragma once

#include "../interface/Pizza.h"
#include "../interface/PizzaIngredientFactory.h"

class PepperoniPizza : public Pizza
{
public:
    explicit PepperoniPizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit PepperoniPizza(std::nullptr_t) = delete;
    virtual ~PepperoniPizza() = default;

    void prepare();

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};