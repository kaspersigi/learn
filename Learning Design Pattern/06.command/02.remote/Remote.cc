#include "Remote.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto remoteControl = std::make_shared<RemoteControl>();
    remoteControl->setCommand(0, new LivingroomLightOnCommand(new Light("Living Room")), new LivingroomLightOffCommand(new Light("Living Room")));

    std::cout << remoteControl->toShow() << std::endl;
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);

    return 0;
}