#pragma once

#include "../interface/Pizza.h"
#include <memory>

class PizzaIngredientFactory;

class PepperoniPizza : public Pizza {
public:
    explicit PepperoniPizza(std::unique_ptr<PizzaIngredientFactory> f);
    explicit PepperoniPizza(std::nullptr_t) = delete;
    ~PepperoniPizza() override;

    void prepare() override;

private:
    std::unique_ptr<PizzaIngredientFactory> _ingredientFactory;
};