#include "Undo.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto remoteControl = std::make_shared<RemoteControlWithUndo>();
    auto light = std::make_shared<Light>("Living Room");

    remoteControl->setCommand(0, std::make_shared<LightOnCommand>(light), std::make_shared<LightOffCommand>(light));
    std::cout << remoteControl->toShow() << std::endl;
    remoteControl->onButtonWasPushed(0);
    remoteControl->undoButtonWasPushed();
    remoteControl->offButtonWasPushed(0);

    remoteControl->onButtonWasPushed(1);
    remoteControl->undoButtonWasPushed();
    remoteControl->offButtonWasPushed(1);

    // 假设灯坏了
    light.reset();
    remoteControl->onButtonWasPushed(0);
    remoteControl->offButtonWasPushed(0);

    return 0;
}