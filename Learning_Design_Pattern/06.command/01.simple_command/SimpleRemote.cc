#include "SimpleRemote.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto remote = std::make_shared<SimpleRemoteControl>();
    auto light = std::make_shared<Light>();

    remote->setCommand(std::make_shared<LightOnCommand>(light));
    remote->buttonWasPressed();
    remote->setCommand(std::make_shared<LightOffCommand>(light));
    remote->buttonWasPressed();

    // 假设灯坏了
    light.reset();
    remote->buttonWasPressed();

    return 0;
}