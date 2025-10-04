#include "DuckSimulator.h"
#include <memory>
#include <print>

auto main(int argc, char* argv[]) -> int
{
    std::unique_ptr<Duck> mallard = std::make_unique<MallardDuck>();
    std::unique_ptr<Duck> rubberDuckie = std::make_unique<RubberDuck>();
    std::unique_ptr<Duck> decoy = std::make_unique<DecoyDuck>();
    std::unique_ptr<Duck> model = std::make_unique<ModelDuck>();

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