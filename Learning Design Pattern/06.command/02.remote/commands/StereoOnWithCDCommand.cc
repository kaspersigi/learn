#include "StereoOnWithCDCommand.h"
#include <iostream>

StereoOnWithCDCommand::StereoOnWithCDCommand(std::shared_ptr<const Stereo> stereo)
    : _stereo(stereo)
{
}

void StereoOnWithCDCommand::execute() const
{
    if (_stereo.use_count()) {
        _stereo.lock()->on();
        _stereo.lock()->setCD();
        _stereo.lock()->setVolume(11);
    } else
        std::cout << "device is broken" << std::endl;
}