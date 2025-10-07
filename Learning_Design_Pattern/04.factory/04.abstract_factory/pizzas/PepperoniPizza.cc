#include "PepperoniPizza.h"
#include "../interface/PizzaIngredientFactory.h"
#include <iostream>

PepperoniPizza::PepperoniPizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

PepperoniPizza::~PepperoniPizza() = default;

void PepperoniPizza::prepare()
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = _ingredientFactory->createDough();
    _sauce = _ingredientFactory->createSauce();
    _cheese = _ingredientFactory->createCheese();
    _pepperoni = _ingredientFactory->createPepperoni();
    if (_veggies.empty())
        _veggies = _ingredientFactory->createVeggies();
}