#include "ChicagoStyleCheesePizza.h"

ChicagoStyleCheesePizza::ChicagoStyleCheesePizza()
{
    _name = "Chicago Style Deep Dish Cheese Pizza";
    _dough = "Extra Thick Crust Dough";
    _sauce = "Plum Tomato Sauce";
    _toppings.push_back("Shredded Mozzarella Cheese");
}

void ChicagoStyleCheesePizza::cut() const { std::cout << "Cutting the pizza into square slices" << std::endl; }