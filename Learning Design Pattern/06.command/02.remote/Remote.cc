#include "Remote.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto remoteControl = std::make_shared<RemoteControl>();
    auto light = std::make_shared<Light>("Living Room");

    remoteControl->setCommand(0, new LivingroomLightOnCommand(light), new LivingroomLightOffCommand(light));
    std::cout << remoteControl->toShow() << std::endl;
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);

    remoteControl->onButtonWasPushed(1);
    remoteControl->offButtonWasPushed(1);

    // 假设灯坏了
    light.reset();
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);

    return 0;
}