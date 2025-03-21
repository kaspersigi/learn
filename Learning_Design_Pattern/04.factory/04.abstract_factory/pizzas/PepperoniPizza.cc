#include "PepperoniPizza.h"

PepperoniPizza::PepperoniPizza(PizzaIngredientFactory* ingredientFactory)
    : _ingredientFactory(ingredientFactory)
{
}

void PepperoniPizza::prepare() const
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = std::shared_ptr<Dough>(_ingredientFactory->createDough());
    _sauce = std::shared_ptr<Sauce>(_ingredientFactory->createSauce());
    _cheese = std::shared_ptr<Cheese>(_ingredientFactory->createCheese());
    _pepperoni = std::shared_ptr<Pepperoni>(_ingredientFactory->createPepperoni());
    if (_veggies.empty())
        _veggies = _ingredientFactory->createVeggies();
}