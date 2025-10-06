#include "ClamPizza.h"
#include <iostream>

ClamPizza::ClamPizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

void ClamPizza::prepare()
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = _ingredientFactory->createDough();
    _sauce = _ingredientFactory->createSauce();
    _cheese = _ingredientFactory->createCheese();
    _clam = _ingredientFactory->createClams();
}