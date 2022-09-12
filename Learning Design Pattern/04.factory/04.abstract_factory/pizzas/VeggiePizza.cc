#include "VeggiePizza.h"

VeggiePizza::VeggiePizza(PizzaIngredientFactory* ingredientFactory)
    : _ingredientFactory(ingredientFactory)
{
}

void VeggiePizza::prepare() const
{
    std::cout << "Preparing " << getName() << std::endl;
    _dough = std::shared_ptr<Dough>(_ingredientFactory->createDough());
    _sauce = std::shared_ptr<Sauce>(_ingredientFactory->createSauce());
    _cheese = std::shared_ptr<Cheese>(_ingredientFactory->createCheese());
    if (_veggies.empty())
        _veggies = _ingredientFactory->createVeggies();
}