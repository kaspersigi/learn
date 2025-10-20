#pragma once
#include "../devices/Stereo.h"
#include "../interface/Command.h"
#include <memory>

class StereoOffCommand : public Command
{
public:
    explicit StereoOffCommand(const std::shared_ptr<const Stereo>& stereo);
    explicit StereoOffCommand(std::nullptr_t) = delete;
    virtual ~StereoOffCommand();

    void execute() const;

private:
    std::weak_ptr<const Stereo> _stereo {};
};