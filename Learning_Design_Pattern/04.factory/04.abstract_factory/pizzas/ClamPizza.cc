#include "ClamPizza.h"
#include "../interface/PizzaIngredientFactory.h"
#include <iostream>

ClamPizza::ClamPizza(std::unique_ptr<PizzaIngredientFactory> f)
    : _ingredientFactory(std::move(f))
{
}

ClamPizza::~ClamPizza() = default;

void ClamPizza::prepare()
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = _ingredientFactory->createDough();
    _sauce = _ingredientFactory->createSauce();
    _cheese = _ingredientFactory->createCheese();
    _clam = _ingredientFactory->createClams();
}