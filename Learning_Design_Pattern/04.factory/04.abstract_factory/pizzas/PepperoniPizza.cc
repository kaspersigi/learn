#include "PepperoniPizza.h"
#include <iostream>

PepperoniPizza::PepperoniPizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

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