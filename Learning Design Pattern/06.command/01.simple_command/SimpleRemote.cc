#include "SimpleRemote.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<SimpleRemoteControl> remote(new SimpleRemoteControl());

    std::shared_ptr<Light> light(new Light());
    std::shared_ptr<GarageDoor> garageDoor(new GarageDoor());

    std::shared_ptr<LightOnCommand> lightOn(new LightOnCommand(light.get()));
    std::shared_ptr<GarageDoorOpenCommand> garageOpen(new GarageDoorOpenCommand(garageDoor.get()));

    remote->setCommand(lightOn.get());
    remote->buttonWasPressed();
    remote->setCommand(garageOpen.get());
    remote->buttonWasPressed();

    return 0;
}