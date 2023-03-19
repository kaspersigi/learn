#include "DuckSimulator.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
    std::shared_ptr<Duck> rubberDuckie = std::make_shared<RubberDuck>();
    std::shared_ptr<Duck> decoy = std::make_shared<DecoyDuck>();
    std::shared_ptr<Duck> model = std::make_shared<ModelDuck>();

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