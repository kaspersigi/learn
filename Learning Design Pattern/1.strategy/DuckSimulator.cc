#include "DuckSimulator.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto mallard = std::make_shared<MallardDuck>();
    auto rubberDuckie = std::make_shared<RubberDuck>();
    auto decoy = std::make_shared<DecoyDuck>();
    auto model = std::make_shared<ModelDuck>();

    mallard->performQuack();
    mallard->performFly();
    std::cout << "--------------------" << std::endl;

    rubberDuckie->performQuack();
    rubberDuckie->performFly();
    std::cout << "--------------------" << std::endl;

    decoy->performQuack();
    decoy->performFly();
    std::cout << "--------------------" << std::endl;

    model->performQuack();
    model->performFly();
    model->setFlyBehavior(new FlyRocketPowered());
    model->performFly();
    return 0;
}