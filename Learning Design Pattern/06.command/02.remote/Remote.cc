#include "Remote.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<RemoteControl> remote(new RemoteControl());

    remote->setCommand(new LightOnCommand(new Light("Bedroom")));
    remote->buttonWasPressed();
    remote->setCommand(new GarageDoorUpCommand(new GarageDoor("Bedroom")));
    remote->buttonWasPressed();

    return 0;
}