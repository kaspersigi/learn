#include "SimpleRemote.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::shared_ptr<SimpleRemoteControl> remote(new SimpleRemoteControl());

    remote->setCommand(new LightOnCommand(new Light()));
    remote->buttonWasPressed();
    remote->setCommand(new GarageDoorOpenCommand(new GarageDoor()));
    remote->buttonWasPressed();

    return 0;
}