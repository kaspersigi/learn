#include "DuckSimulator.h"
#include <print>

auto main(int argc, char* argv[]) -> int
{
    auto mallard = std::make_unique<MallardDuck>();
    auto rubberDuckie = std::make_unique<RubberDuck>();
    auto decoy = std::make_unique<DecoyDuck>();
    auto model = std::make_unique<ModelDuck>();

    mallard->performQuack();
    mallard->performFly();
    std::println("--------------------");

    rubberDuckie->performQuack();
    rubberDuckie->performFly();
    std::println("--------------------");

    decoy->performQuack();
    decoy->performFly();
    std::println("--------------------");

    model->performQuack();
    model->performFly();
    model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
    model->performFly();

    return 0;
}