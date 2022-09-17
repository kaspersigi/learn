#include "Adapter.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto mallard = std::make_shared<MallardDuck>();
    auto rubberDuckie = std::make_shared<RubberDuck>();
    auto decoy = std::make_shared<DecoyDuck>();
    auto model = std::make_shared<ModelDuck>();
    auto wild = std::make_shared<WildTurkey>();

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
    std::cout << "--------------------" << std::endl;

    wild->performQuack();
    wild->performFly();
    std::cout << "--------------------" << std::endl;

    auto duckAdapter = std::make_shared<DuckAdapter>(new RubberDuck());
    duckAdapter->display();
    duckAdapter->performQuack();
    duckAdapter->performFly();
    std::cout << "--------------------" << std::endl;

    auto turkeyAdapter = std::make_shared<TurkeyAdapter>(new WildTurkey());
    turkeyAdapter->display();
    turkeyAdapter->performQuack();
    turkeyAdapter->performFly();

    return 0;
}